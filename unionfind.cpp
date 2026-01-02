#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UF {
    private:
        vi p, rank, setSize;
        int _numsets;
    public:
        UF(int N) : p(N), rank(N, 0), setSize(N, 1), _numsets(N) {
            std::iota(p.begin(), p.end(), 0);
        }

        int find(int i) { return p[i] == i ? i : p[i] = find(p[i]); }
        bool same(int i, int j) { return find(i) == find(j); }
        int numsets() { return _numsets; }
        int setsize(int i) { return setSize[find(i)]; }

        void unions(int i, int j) {
            if(same(i,j)) { return; }
            int x = find(i), y = find(j);
            if (rank[x] > rank[y]) { swap(x,y); }
            p[x] = y;
            if(rank[x] == rank[y]) { ++rank[y]; }
            setSize[y] += setSize[x];
            --_numsets;
        }
};

int main() {
    UF uf(5);
    printf("%d\n", uf.numsets());
    uf.unions(0,1);
    printf("%d\n", uf.numsets());
    uf.unions(2,3);
    printf("%d\n", uf.numsets());
    uf.unions(4,3);
    printf("%d\n", uf.numsets());
    printf("uf.same(0,3) == %d\n", uf.same(0,3));
    printf("uf.same(4,3) == %d\n", uf.same(4,3));
    for (int i = 0; i < 5; ++i) {
        printf("uf.find(%d) == %d, uf.setsize(%d) == %d\n",
                i, uf.find(i), i, uf.setsize(i));
    }
    uf.unions(0,3);
    printf("%d\n", uf.numsets());
    for (int i = 0; i < 5; ++i) {
        printf("uf.find(%d) == %d, uf.setsize(%d) == %d\n",
                i, uf.find(i), i, uf.setsize(i));
    }
}
