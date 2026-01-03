add_executable(test_fenwick test_fenwick.cpp)
target_link_libraries(test_fenwick cp)
add_test(NAME test_fenwick COMMAND test_fenwick)

add_executable(test_gen_perms test_gen_perms.cpp)
target_link_libraries(test_gen_perms cp)
add_test(NAME test_gen_perms COMMAND test_gen_perms)

add_executable(test_heaps_alg test_heaps_alg.cpp)
target_link_libraries(test_heaps_alg cp)
add_test(NAME test_heaps_alg COMMAND test_heaps_alg)

add_executable(test_pbds test_pbds.cpp)
target_link_libraries(test_pbds cp)
add_test(NAME test_pbds COMMAND test_pbds)

add_executable(test_scanf_demo test_scanf_demo.cpp)
target_link_libraries(test_scanf_demo cp)
add_test(NAME test_scanf_demo COMMAND test_scanf_demo)

add_executable(test_rmq_segtree test_rmq_segtree.cpp)
target_link_libraries(test_rmq_segtree cp)
add_test(NAME test_rmq_segtree COMMAND test_rmq_segtree)

add_executable(test_point_segtree test_point_segtree.cpp)
target_link_libraries(test_point_segtree cp)
add_test(NAME test_point_segtree COMMAND test_point_segtree)

add_executable(test_unionfind test_unionfind.cpp)
target_link_libraries(test_unionfind cp)
add_test(NAME test_unionfind COMMAND test_unionfind)
