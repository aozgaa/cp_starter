#include "unionfind.hpp"

#include <cstdio>

int main() {
    UF uf(5);
    std::printf("%d\n", uf.numsets());
    uf.unions(0, 1);
    std::printf("%d\n", uf.numsets());
    uf.unions(2, 3);
    std::printf("%d\n", uf.numsets());
    uf.unions(4, 3);
    std::printf("%d\n", uf.numsets());
    std::printf("uf.same(0,3) == %d\n", uf.same(0, 3));
    std::printf("uf.same(4,3) == %d\n", uf.same(4, 3));
    for (int i = 0; i < 5; ++i) {
        std::printf("uf.find(%d) == %d, uf.setsize(%d) == %d\n",
                    i, uf.find(i), i, uf.setsize(i));
    }
    uf.unions(0, 3);
    std::printf("%d\n", uf.numsets());
    for (int i = 0; i < 5; ++i) {
        std::printf("uf.find(%d) == %d, uf.setsize(%d) == %d\n",
                    i, uf.find(i), i, uf.setsize(i));
    }
    return 0;
}
