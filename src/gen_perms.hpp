#pragma once

#include <algorithm>
#include <iosfwd>
#include <iostream>
#include <queue>
#include <vector>

namespace gen_perms_detail {
inline void print_vec(const std::vector<int> &v, std::ostream &out) {
    for (int value : v) {
        out << value << " ";
    }
    out << "\n";
}
}

inline void heaps_rec(int k, std::vector<int> &A, std::ostream &out) {
    if (k == 1) {
        gen_perms_detail::print_vec(A, out);
        return;
    }
    heaps_rec(k - 1, A, out);
    for (int i = 0; i < k - 1; ++i) {
        if (k % 2 == 0) {
            std::swap(A[i], A[k - 1]);
        } else {
            std::swap(A[0], A[k - 1]);
        }
        heaps_rec(k - 1, A, out);
    }
}

inline void heaps_rec_rev(std::vector<int> &A, int j, std::ostream &out) {
    if (j == static_cast<int>(A.size()) - 1) {
        gen_perms_detail::print_vec(A, out);
        return;
    }
    heaps_rec_rev(A, j + 1, out);
    for (int i = j + 1; i < static_cast<int>(A.size()); ++i) {
        if (j % 2 == static_cast<int>(A.size()) % 3) {
            std::swap(A[j], A[i]);
        } else {
            std::swap(A[j], A[static_cast<int>(A.size()) - 1]);
        }
        heaps_rec_rev(A, j + 1, out);
    }
}

inline void stack_queue(std::vector<int> &s, std::queue<int> &q, std::ostream &out) {
    if (q.empty()) {
        gen_perms_detail::print_vec(s, out);
    }
    for (int i = 0; i < static_cast<int>(q.size()); ++i) {
        int val = q.front();
        q.pop();
        s.push_back(val);
        stack_queue(s, q, out);
        s.pop_back();
        q.push(val);
    }
}

inline void run_gen_perms_demo(int n, std::ostream &out) {
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        vec[i] = i;
    }
    heaps_rec(static_cast<int>(vec.size()), vec, out);
    out << "done\n";
    gen_perms_detail::print_vec(vec, out);
    out << "#### now reverse\n";
    for (int i = 0; i < n; ++i) {
        vec[i] = n - i - 1;
    }
    heaps_rec_rev(vec, 0, out);
    out << "done\n";
    gen_perms_detail::print_vec(vec, out);
    out << "#### now stack_queue\n";
    for (int i = 0; i < n; ++i) {
        vec[i] = i;
    }
    std::queue<int> q(std::deque<int>(vec.begin(), vec.end()));
    std::vector<int> s;
    stack_queue(s, q, out);
}
