#pragma once

#include <vector>

class FT {
public:
    explicit FT(int m);
    explicit FT(const std::vector<int> &f);
    FT(int m, const std::vector<int> &s);

    int rsq(int j);
    int rsq(int i, int j);
    void update(int i, int v);
    int select(int k);

private:
    std::vector<int> ft;

    static int ls_one(int s);
    void build(const std::vector<int> &f);
};

inline int FT::ls_one(int s) {
    return s & (-s);
}

inline void FT::build(const std::vector<int> &f) {
    int m = static_cast<int>(f.size()) - 1;
    ft.assign(m + 1, 0);
    for (int i = 1; i <= m; ++i) {
        ft[i] += f[i];
        if (i + ls_one(i) <= m) {
            ft[i + ls_one(i)] += ft[i];
        }
    }
}

inline FT::FT(int m) : ft(m + 1, 0) {}

inline FT::FT(const std::vector<int> &f) {
    build(f);
}

inline FT::FT(int m, const std::vector<int> &s) {
    std::vector<int> f(m + 1, 0);
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        ++f[s[i]];
    }
    build(f);
}

inline int FT::rsq(int j) {
    int sum = 0;
    while (j) {
        sum += ft[j];
        j -= ls_one(j);
    }
    return sum;
}

inline int FT::rsq(int i, int j) {
    return rsq(j) - rsq(i);
}

inline void FT::update(int i, int v) {
    while (i < static_cast<int>(ft.size())) {
        ft[i] += v;
        i += ls_one(i);
    }
}

inline int FT::select(int k) {
    int lo = 1;
    int hi = static_cast<int>(ft.size()) - 1;
    for (int i = 0; i < 8 * static_cast<int>(sizeof(int)); ++i) {
        int mid = (lo / 2) + (hi / 2) + (1 & (lo & hi));
        if (rsq(mid) < k) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return hi;
}
