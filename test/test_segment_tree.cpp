#include "segment_tree.hpp"

#include <cstdio>
#include <vector>

int main() {
    std::vector<int> A = {18, 17, 13, 19, 15, 11, 20, 99};
    SegmentTree st(A);

    std::printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
    std::printf("              A is {18,17,13,19,15,11,20,oo}\n");
    std::printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));
    std::printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));
    std::printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));

    st.update(5, 5, 77);
    std::printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
    std::printf("Now, modify A into {18,17,13,19,15,77,20,oo}\n");
    std::printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));
    std::printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));
    std::printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));

    st.update(0, 3, 30);
    std::printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
    std::printf("Now, modify A into {30,30,30,30,15,77,20,oo}\n");
    std::printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));
    std::printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));
    std::printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));

    st.update(3, 3, 7);
    std::printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
    std::printf("Now, modify A into {30,30,30, 7,15,77,20,oo}\n");
    std::printf("RMQ(1, 3) = %d\n", st.RMQ(1, 3));
    std::printf("RMQ(4, 7) = %d\n", st.RMQ(4, 7));
    std::printf("RMQ(3, 4) = %d\n", st.RMQ(3, 4));

    return 0;
}
