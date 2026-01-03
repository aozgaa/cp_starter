#pragma once

#include<concepts>
#include<cassert>
#include<span>
#include <type_traits>
#include <utility>
#include<vector>

using VI = std::vector<int>;
using SI = std::span<int>;

template<typename Traits>
concept MonoidTraitsConcept = requires() {
  typename Traits::T;
  typename Traits::Op;
  { Traits::e() } -> std::same_as<typename Traits::T>;
};

constexpr size_t next_pow2(size_t n) {
  auto i = 1ll;
  for(; i < n; i <<= 1);
  return i;  
}

constexpr size_t log2(size_t n) {
  auto i = 0ll; 
  for(; (1<<i) < n; i++);
  return i;
}

template<MonoidTraitsConcept Traits>
struct SegTree {
  using T = typename Traits::T;
  using Op = typename Traits::Op;
  constexpr static T e() { return Traits::e(); }

  using Key = size_t;
  using VT = std::vector<T>;

  SegTree(size_t n) : n_{n}, sz_{next_pow2(n)}, lsz_{log2(sz_)}, tree_(sz_*2,e()) {} 
  SegTree(VT vs) : SegTree{vs.size()} { for(int i = 0; i < n_; ++i) set(i,vs[i]); }

  // update tree
  void set(Key k, T x);
  // returns: value of tree at a point
  T pquery(Key k);
  // returns: aggregation of tree over range [l,r)
  T rquery(Key l, Key r);
  // returns: aggregation over entire tree
  T rquery();
  // assume: predicate f is monotone for rquery(l, i) as i increases and f(e()) is true
  // returns: max index i such that f(rquery(l, i)) is true
  template<class F>
    Key max_true_idx(Key l, F&& f);
  // assume: predicate f is monotone for rquery(i, r) as i decreases and f(e()) is true
  // returns: min index i such that f(rquery(i, r)) is true
  template<class F>
    Key min_true_idx(Key r, F&& f);

  private:
  const size_t n_;
  const size_t sz_;
  const size_t lsz_;
  VT tree_;

};

template<MonoidTraitsConcept Traits>
void SegTree<Traits>::set(Key k, T x) {
  k += sz_;
  tree_[k]= x;
  for(k >>= 1; k > 0; k >>= 1) {
    tree_[k] = Op(tree_[k*2],tree_[k*2+1]);
  }
}

template<MonoidTraitsConcept Traits>
typename SegTree<Traits>::T SegTree<Traits>::pquery(Key k) {
  return tree_[k+sz_];
}

template<MonoidTraitsConcept Traits>
typename SegTree<Traits>::T SegTree<Traits>::rquery(Key l, Key r) {
  T lv=e(), rv=e();
  l += sz_;
  r += sz_;
  while(l < r) {
    if(l&1) /*is right subchild*/ lv=Op(lv,tree_[l++]);  
    if(r&1) /*is left subchild*/ rv=Op(tree_[--r],rv);
    l>>=1;
    r>>=1;
  }
  return Op(lv,rv);
}

template<MonoidTraitsConcept Traits>
typename SegTree<Traits>::T SegTree<Traits>::rquery() { return tree_[1]; }

template<MonoidTraitsConcept Traits>
template<class F>
typename SegTree<Traits>::Key SegTree<Traits>::max_true_idx(Key l, F&& f) {
  using Fn = std::remove_cvref_t<F>;
  static_assert(std::is_invocable_r_v<bool, Fn, T>);
  assert(l <= n_);
  assert(f(e()));

  if (l == n_) return n_;

  auto cur = l + sz_; // working range query end
  T rq = e(); // working range query result
  for(;;) {
    while((cur & 1) == 0) cur >>= 1; // climb until we have a disjoint segment containing the current cursor
    if (f(Op(rq, tree_[cur]))) { // pred still true over [l,r)
      rq = Op(rq, tree_[cur]);
      cur++; // go rightward to a left node
    } else { // pred became false somewhere in range
      while(cur < sz_) {
        cur <<= 1; // descend left
        if (f(Op(rq, tree_[cur]))) {
          rq = Op(rq,tree_[cur]);
          cur++; // go to adjacent right node
        }
      }
      return cur - sz_;
    }
    if ((cur & -cur) == cur) return n_; // power-of-two means the segment now spans to the far right
  }
  std::unreachable();
}

template<MonoidTraitsConcept Traits>
template<class F>
typename SegTree<Traits>::Key SegTree<Traits>::min_true_idx(Key r, F&& f) {
  using Fn = std::remove_cvref_t<F>;
  static_assert(std::is_invocable_r_v<bool, Fn, T>);
  assert(r <= n_);
  assert(f(e()));

  if(r == 0) return 0;
  auto cur = r + sz_; // working range query end
  T rq = e(); // working range query result
  for(;;) {
    --cur; // move to the last in-range leaf
    while(cur > 1 && (cur & 1)) cur >>= 1; // climb until we have a disjoint segment containing the current cursor
    if (f(Op(tree_[cur], rq))) { // pred still true over [l,r)
      rq = Op(tree_[cur], rq);
    } else { // pred became false somewhere in range
      while(cur < sz_) {
        cur = (cur<<1) + 1; // descend right
        if (f(Op(tree_[cur], rq))) {
          rq = Op(tree_[cur], rq);
          cur--; // go leftward to right node
        }
      }
      return cur + 1 - sz_;
    }
    if ((cur & -cur) == cur) return 0; // power-of-two means the segment now spans to the far left
  }
}
