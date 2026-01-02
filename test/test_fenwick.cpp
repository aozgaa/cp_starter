#include "fenwick.hpp"

#include <cstdio>

int main() {
    FT ft(1 << 4);
    ft.update(7, 3);
    for (int i = 0; i <= (1 << 4); ++i) {
        std::printf("ft.rsq(%d) == %d\n", i, ft.rsq(i));
        std::printf("ft.select(%d) == %d\n", i, ft.select(i));
    }
    return 0;
}
