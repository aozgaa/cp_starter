#include "scanf_demo.hpp"

#include <iostream>
#include <sstream>

int main() {
    std::istringstream input("1 2 3 4 0 9 9 9");
    run_scanf_demo(input, std::cout);
    return 0;
}
