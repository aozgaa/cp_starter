#pragma once

#include <numeric>
#include <utility>
#include <vector>

class UF {
public:
    explicit UF(int N);

    int find(int i);
    bool same(int i, int j);
    int numsets();
    int setsize(int i);
    void unions(int i, int j);

private:
    std::vector<int> p;
    std::vector<int> rank;
    std::vector<int> setSize;
    int numsets_count;
};

inline UF::UF(int N) : p(N), rank(N, 0), setSize(N, 1), numsets_count(N) {
    std::iota(p.begin(), p.end(), 0);
}

inline int UF::find(int i) {
    return p[i] == i ? i : p[i] = find(p[i]);
}

inline bool UF::same(int i, int j) {
    return find(i) == find(j);
}

inline int UF::numsets() {
    return numsets_count;
}

inline int UF::setsize(int i) {
    return setSize[find(i)];
}

inline void UF::unions(int i, int j) {
    if (same(i, j)) {
        return;
    }
    int x = find(i);
    int y = find(j);
    if (rank[x] > rank[y]) {
        std::swap(x, y);
    }
    p[x] = y;
    if (rank[x] == rank[y]) {
        ++rank[y];
    }
    setSize[y] += setSize[x];
    --numsets_count;
}
