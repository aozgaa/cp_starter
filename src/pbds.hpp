#pragma once

#include <bits/extc++.h>
#include <iosfwd>
#include <ostream>

using namespace __gnu_pbds;

typedef tree<int, null_type, std::less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ost;

inline void run_pbds_demo(std::ostream &out) {
    int n = 9;
    int A[] = {2, 4, 7, 10, 15, 23, 50, 65, 71};
    ost tree;
    for (int i = 0; i < n; ++i) {
        tree.insert(A[i]);
    }
    out << *tree.find_by_order(0) << "\n";
    out << *tree.find_by_order(n - 1) << "\n";
    out << *tree.find_by_order(4) << "\n";
    out << tree.order_of_key(2) << "\n";
    out << tree.order_of_key(71) << "\n";
    out << tree.order_of_key(15) << "\n";
}
