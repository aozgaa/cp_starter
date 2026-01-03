#include "segtree2.hpp"

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <random>
#include <string>
#include <vector>

struct SumTraits {
  using T = int;
  struct Op {
    int v;
    Op(int a, int b) : v(a + b) {}
    operator int() const { return v; }
  };
  static int e() { return 0; }
};

struct MaxTraits {
  using T = int;
  struct Op {
    int v;
    Op(int a, int b) : v(std::max(a, b)) {}
    operator int() const { return v; }
  };
  static int e() { return std::numeric_limits<int>::min(); }
};

struct ConcatTraits {
  using T = std::string;
  struct Op {
    std::string v;
    Op(const std::string& a, const std::string& b) : v(a + b) {}
    operator std::string() const { return v; }
  };
  static std::string e() { return ""; }
};

void assert_eq(int got, int want, const char* msg) {
  if (got != want) {
    std::fprintf(stderr, "assert_eq failed: %s (got=%d, want=%d)\n", msg, got, want);
    std::abort();
  }
}

void assert_eq_str(const std::string& got, const std::string& want, const char* msg) {
  if (got != want) {
    std::fprintf(stderr, "assert_eq_str failed: %s (got=%s, want=%s)\n",
                 msg, got.c_str(), want.c_str());
    std::abort();
  }
}

void assert_eq_size(size_t got, size_t want, const char* msg) {
  if (got != want) {
    std::fprintf(stderr, "assert_eq_size failed: %s (got=%zu, want=%zu)\n", msg, got, want);
    std::abort();
  }
}

template <typename ST, typename F>
size_t naive_max_right(ST& st, size_t n, size_t l, F f) {
  for (size_t r = l; r <= n; ++r) {
    if (!f(st.rquery(l, r))) return r - 1;
  }
  return n;
}

template <typename ST, typename F>
size_t naive_min_left(ST& st, size_t r, F f) {
  size_t l = r;
  while (l > 0 && f(st.rquery(l - 1, r))) --l;
  return l;
}

void test_sum_basic() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  SegTree<SumTraits> st(v);

  assert_eq(st.pquery(0), 1, "sum pquery first");
  assert_eq(st.pquery(4), 5, "sum pquery last");
  assert_eq(st.rquery(0, 5), 15, "sum rquery full");
  assert_eq(st.rquery(1, 4), 9, "sum rquery mid");
  assert_eq(st.rquery(2, 3), 3, "sum rquery single");
  assert_eq(st.rquery(4, 5), 5, "sum rquery tail");

  for (int i = 0; i <= 5; ++i) {
    assert_eq(st.rquery(i, i), 0, "sum rquery empty");
  }

  st.set(2, 10);
  assert_eq(st.pquery(2), 10, "sum set update");
  assert_eq(st.rquery(0, 5), 22, "sum rquery after set");

  st.set(2, 10);
  assert_eq(st.rquery(2, 3), 10, "sum repeated set same value");

  st.set(2, -1);
  assert_eq(st.pquery(2), -1, "sum repeated set new value");
  assert_eq(st.rquery(0, 5), 11, "sum rquery after repeated set");
}

void test_sum_ones() {
  for(int n = 1; n <= 128; ++n) {
    std::vector<int> vs(n,1);
    SegTree<SumTraits> st(vs);

    for(int i = 0; i < n; ++i) {
      assert_eq(st.pquery(i), vs[i], "entries should be one");
    }

    assert(st.rquery() == n);

    for(int l = 0; l < n; ++l) {
      for(int r = l; r < n; ++r) {
        assert_eq(st.rquery(l,r), r-l, "range query should be width fo interval");
      }
    }

    for(int l = 0; l < n; ++l) {
      for(int r=l; r<n; ++r) {
        assert_eq(st.max_true_idx(l, [&](int k) { return k <= r-l; }), r, "max_true_idx is width of interval");
        assert_eq(st.min_true_idx(r, [&](int k) { return k <= r-l; }), l, "max_true_idx is width of interval");
      }
    }
  }
}

void test_sum_rng() {
  std::mt19937 rng(42);
  std::uniform_int_distribution<int> dist(0, 20);

  for(int n = 1; n <= 64; ++n) {
    std::vector<int> vs(n);
    for(int i = 0; i < n; ++i) vs[i] = dist(rng);
    SegTree<SumTraits> st(vs);

    std::vector<int> pref(n + 1, 0);
    for(int i = 0; i < n; ++i) pref[i + 1] = pref[i] + vs[i];

    for(int i = 0; i < n; ++i)
      assert_eq(st.pquery(i), vs[i], "rng pquery matches");

    for(int l = 0; l <= n; ++l) {
      for(int r = l; r <= n; ++r) {
        int want = pref[r] - pref[l];
        assert_eq(st.rquery(l, r), want, "rng rquery matches");
      }
    }

    for(int l = 0; l <= n; ++l) {
      for(int r = l; r <= n; ++r) {
        int limit = pref[r] - pref[l];
        auto f = [limit](int x) { return x <= limit; };
        size_t want_r = naive_max_right(st, n, l, f);
        assert_eq_size(st.max_true_idx(l, f), want_r, "rng max_true_idx matches");
        size_t want_l = naive_min_left(st, r, f);
        assert_eq_size(st.min_true_idx(r, f), want_l, "rng min_true_idx matches");
      }
    }
  }
}

void test_sum_singleton() {
  SegTree<SumTraits> st(std::vector<int>{7});
  assert_eq(st.pquery(0), 7, "sum singleton pquery");
  assert_eq(st.rquery(0, 1), 7, "sum singleton rquery");
  assert_eq(st.rquery(0, 0), 0, "sum singleton empty");
  assert_eq(st.rquery(1, 1), 0, "sum singleton empty end");

  st.set(0, 2);
  assert_eq(st.pquery(0), 2, "sum singleton set 2");
  st.set(0, 5);
  assert_eq(st.pquery(0), 5, "sum singleton set 5");
  assert_eq(st.rquery(0, 1), 5, "sum singleton rquery after set");
}

void test_sum_edge_cases() {
  std::vector<int> sizes = {1, 2, 3, 7, 8, 9, 15, 16, 17};
  for (int n : sizes) {
    std::vector<int> vs(n, 0);
    SegTree<SumTraits> st(vs);

    assert_eq(st.rquery(), 0, "sum all_prod zero");
    for (int i = 0; i <= n; ++i) {
      assert_eq(st.rquery(i, i), 0, "sum empty range");
    }

    auto f = [](int x) { return x < 1; };
    assert_eq_size(st.max_true_idx(n, f), n, "sum max_true_idx l==n");
    assert_eq_size(st.min_true_idx(0, f), 0, "sum min_true_idx r==0");

    for (int l = 0; l <= n; ++l) {
      assert_eq_size(st.max_true_idx(l, f), n, "sum max_true_idx all zero");
    }
    for (int r = 0; r <= n; ++r) {
      assert_eq_size(st.min_true_idx(r, f), 0, "sum min_true_idx all zero");
    }

    st.set(0, 0);
    assert_eq(st.rquery(), 0, "sum all_prod zero after set");
  }
}

void test_max_basic() {
  std::vector<int> v = {1, -2, 3, 4, 5};
  SegTree<MaxTraits> st(v);

  assert_eq(st.pquery(0), 1, "max pquery first");
  assert_eq(st.pquery(4), 5, "max pquery last");
  assert_eq(st.rquery(0, 5), 5, "max rquery full");
  assert_eq(st.rquery(1, 4), 4, "max rquery mid");
  assert_eq(st.rquery(2, 3), 3, "max rquery single");
  assert_eq(st.rquery(4, 5), 5, "max rquery tail");

  for (int i = 0; i <= 5; ++i) {
    assert_eq(st.rquery(i, i), INT_MIN, "max rquery empty");
  }

  st.set(4, -7);
  assert_eq(st.pquery(4), -7, "max set update");
  assert_eq(st.rquery(0, 5), 4, "max rquery after set");

  st.set(4, -7);
  assert_eq(st.rquery(4, 5), -7, "max repeated set same value");

  st.set(1, 99);
  assert_eq(st.rquery(0, 5), 99, "max rquery after large set");
}

void test_sum_max_right() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  SegTree<SumTraits> st(v);
  const size_t n = v.size();

  for (int limit : {1, 3, 6, 10, 15, 16}) {
    auto f = [limit](int x) { return std::less<int>{}(x, limit); };
    for (size_t l = 0; l <= n; ++l) {
      size_t got = st.max_true_idx(static_cast<int>(l), f);
      size_t want = naive_max_right(st, n, l, f);
      assert_eq_size(got, want, "sum max_right vs naive");
    }
  }

  st.set(1, 5);
  st.set(1, 5);
  st.set(4, 0);
  for (int limit : {1, 5, 7, 9, 12, 20}) {
    auto f = [limit](int x) { return std::less<int>{}(x, limit); };
    for (size_t l = 0; l <= n; ++l) {
      size_t got = st.max_true_idx(static_cast<int>(l), f);
      size_t want = naive_max_right(st, n, l, f);
      assert_eq_size(got, want, "sum max_right vs naive after set");
    }
  }

  auto always_true = [](int x) { return std::less<int>{}(x, 1000); };
  assert_eq_size(st.max_true_idx(static_cast<int>(n), always_true), n, "sum max_right l==n");
}

void test_max_max_right() {
  std::vector<int> v = {1, -2, 3, 4, 5};
  SegTree<MaxTraits> st(v);
  const size_t n = v.size();

  for (int limit : {-3, -2, 0, 3, 4, 5, 6}) {
    auto f = [limit](int x) { return std::less<int>{}(x, limit); };
    for (size_t l = 0; l <= n; ++l) {
      size_t got = st.max_true_idx(static_cast<int>(l), f);
      size_t want = naive_max_right(st, n, l, f);
      assert_eq_size(got, want, "max max_right vs naive");
    }
  }

  st.set(0, -5);
  st.set(2, 8);
  for (int limit : {-5, -1, 3, 7, 8, 9}) {
    auto f = [limit](int x) { return std::less<int>{}(x, limit); };
    for (size_t l = 0; l <= n; ++l) {
      size_t got = st.max_true_idx(static_cast<int>(l), f);
      size_t want = naive_max_right(st, n, l, f);
      assert_eq_size(got, want, "max max_right vs naive after set");
    }
  }

  auto always_true = [](int x) { return std::less<int>{}(x, 1000); };
  assert_eq_size(st.max_true_idx(static_cast<int>(n), always_true), n, "max max_right l==n");
}

void test_concat_order() {
  std::vector<std::string> v = {"a", "b", "c", "d", "e"};
  SegTree<ConcatTraits> st(v);

  assert_eq_str(st.pquery(0), std::string("a"), "concat pquery first");
  assert_eq_str(st.pquery(4), std::string("e"), "concat pquery last");
  assert_eq_str(st.rquery(0, 5), std::string("abcde"), "concat rquery full");
  assert_eq_str(st.rquery(1, 4), std::string("bcd"), "concat rquery mid");
  assert_eq_str(st.rquery(2, 3), std::string("c"), "concat rquery single");

  st.set(2, std::string("X"));
  assert_eq_str(st.rquery(0, 5), std::string("abXde"), "concat rquery after set");
  assert_eq_str(st.rquery(2, 4), std::string("Xd"), "concat rquery after set mid");
}

int main() {
  test_sum_basic();
  test_sum_ones();
  test_sum_rng();
  test_sum_singleton();
  test_sum_edge_cases();
  test_max_basic();
  test_sum_max_right();
  test_max_max_right();
  test_concat_order();
  return 0;
}
