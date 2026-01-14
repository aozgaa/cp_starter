cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)

project(cp_starter)

add_library(cp INTERFACE)

target_sources(cp
  INTERFACE
  FILE_SET HEADERS
  BASE_DIRS src
  FILES
  src/backtrack.hpp
  src/fenwick.hpp
  src/gen_perms.hpp
  src/heaps_alg.hpp
  src/kosaraju.hpp
  src/pbds.hpp
  src/scanf_demo.hpp
  src/rmq_segtree.hpp
  src/unionfind.hpp
)

include(CTest)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
