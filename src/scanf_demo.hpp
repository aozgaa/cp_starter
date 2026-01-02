#pragma once

#include <iosfwd>
#include <iostream>

inline void run_scanf_demo(std::istream &in, std::ostream &out) {
    for (;;) {
        int n[4] = {0, 0, 0, 0};
        for (int i = 0; i < 4; ++i) {
            if (!(in >> n[i])) {
                return;
            }
            out << static_cast<char>(n[i] + '0') << "\n";
        }
        if (n[0] == 0) {
            break;
        }
    }
}
