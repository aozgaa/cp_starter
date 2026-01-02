#pragma once

#include <algorithm>
#include <iosfwd>
#include <iostream>
#include <vector>

namespace heaps_detail {
inline void print_vec(const std::vector<int> &v, std::ostream &out) {
    for (int value : v) {
        out << value << " ";
    }
    out << "\n";
}
}

inline void heaps(std::vector<int> &A, int k, std::ostream &out) {
    if (k <= 1) {
        heaps_detail::print_vec(A, out);
        return;
    }
    heaps(A, k - 1, out);
    for (int i = 0; i < k - 1; ++i) {
        if (k % 2 == 0) {
            std::swap(A[i], A[k - 1]);
        } else {
            std::swap(A[0], A[k - 1]);
        }
        heaps(A, k - 1, out);
    }
}

inline void heaps2(std::vector<int> &A, int k, std::ostream &out) {
    if (k <= 0) {
        heaps_detail::print_vec(A, out);
        return;
    }
    heaps2(A, k - 1, out);
    for (int i = 0; i < k; ++i) {
        if (k % 2 == 0) {
            std::swap(A[0], A[k]);
        } else {
            std::swap(A[i], A[k]);
        }
        heaps2(A, k - 1, out);
    }
}

inline void heaps_nr(std::vector<int> &A, std::ostream &out) {
    std::vector<int> ks(A.size() - 1);

    heaps_detail::print_vec(A, out);

    int sp = 1;
    while (sp < static_cast<int>(A.size())) {
        if (ks[sp] < sp) {
            if (sp % 2) {
                std::swap(A[sp], A[ks[sp]]);
            } else {
                std::swap(A[sp], A[0]);
            }
            heaps_detail::print_vec(A, out);
            ks[sp]++;
            sp = 1;
        } else {
            ks[sp] = 0;
            sp++;
        }
    }
}

inline void nr_loop(int n, std::ostream &out) {
    std::vector<int> ks(n - 1);
    out << " ## result ##\n";
    int sp = 1;
    while (sp < n) {
        out << "sp = " << sp << " :: ";
        out << "ks = { ";
        for (int value : ks) {
            out << value << " ";
        }
        out << "}\n";
        if (ks[sp] < sp) {
            out << " ## result ##\n";
            ks[sp]++;
            sp = 1;
        } else {
            ks[sp] = 0;
            sp++;
        }
    }
}

inline void heaps_rev(std::vector<int> &A, int k, std::ostream &out) {
    if (k >= static_cast<int>(A.size()) - 1) {
        heaps_detail::print_vec(A, out);
        return;
    }
    heaps_rev(A, k + 1, out);
    for (int i = k + 1; i < static_cast<int>(A.size()); ++i) {
        if ((static_cast<int>(A.size()) - k) % 2) {
            std::swap(A[k], A[static_cast<int>(A.size()) - 1]);
        } else {
            std::swap(A[k], A[i]);
        }
        heaps_rev(A, k + 1, out);
    }
}

inline void run_heaps_demo(int n, std::ostream &out) {
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = i;
    }
    nr_loop(n, out);
}
