#pragma once

#include <algorithm>
#include <vector>

class SegmentTree {
public:
    explicit SegmentTree(int sz);
    explicit SegmentTree(const std::vector<int> &initialA);

    void update(int i, int j, int val);
    int RMQ(int i, int j);

private:
    int n;
    std::vector<int> A;
    std::vector<int> st;
    std::vector<int> lazy;

    static int l(int p);
    static int r(int p);
    static int conquer(int a, int b);

    void build(int p, int L, int R);
    void propagate(int p, int L, int R);
    int RMQ(int p, int L, int R, int i, int j);
    void update(int p, int L, int R, int i, int j, int val);
};

inline int SegmentTree::l(int p) {
    return p << 1;
}

inline int SegmentTree::r(int p) {
    return (p << 1) + 1;
}

inline int SegmentTree::conquer(int a, int b) {
    if (a == -1) {
        return b;
    }
    if (b == -1) {
        return a;
    }
    return std::min(a, b);
}

inline SegmentTree::SegmentTree(int sz) : n(sz), st(4 * n), lazy(4 * n, -1) {}

inline SegmentTree::SegmentTree(const std::vector<int> &initialA)
    : SegmentTree(static_cast<int>(initialA.size())) {
    A = initialA;
    build(1, 0, n - 1);
}

inline void SegmentTree::build(int p, int L, int R) {
    if (L == R) {
        st[p] = A[L];
    } else {
        int m = (L + R) / 2;
        build(l(p), L, m);
        build(r(p), m + 1, R);
        st[p] = conquer(st[l(p)], st[r(p)]);
    }
}

inline void SegmentTree::propagate(int p, int L, int R) {
    if (lazy[p] != -1) {
        st[p] = lazy[p];
        if (L != R) {
            lazy[l(p)] = lazy[r(p)] = lazy[p];
        } else {
            A[L] = lazy[p];
        }
        lazy[p] = -1;
    }
}

inline int SegmentTree::RMQ(int p, int L, int R, int i, int j) {
    propagate(p, L, R);
    if (i > j) {
        return -1;
    }
    if ((L >= i) && (R <= j)) {
        return st[p];
    }
    int m = (L + R) / 2;
    return conquer(RMQ(l(p), L, m, i, std::min(m, j)),
                   RMQ(r(p), m + 1, R, std::max(i, m + 1), j));
}

inline void SegmentTree::update(int p, int L, int R, int i, int j, int val) {
    propagate(p, L, R);
    if (i > j) {
        return;
    }
    if ((L >= i) && (R <= j)) {
        lazy[p] = val;
        propagate(p, L, R);
    } else {
        int m = (L + R) / 2;
        update(l(p), L, m, i, std::min(m, j), val);
        update(r(p), m + 1, R, std::max(i, m + 1), j, val);
        int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
        int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
        st[p] = (lsubtree <= rsubtree) ? st[l(p)] : st[r(p)];
    }
}

inline void SegmentTree::update(int i, int j, int val) {
    update(1, 0, n - 1, i, j, val);
}

inline int SegmentTree::RMQ(int i, int j) {
    return RMQ(1, 0, n - 1, i, j);
}
