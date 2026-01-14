#include "kosaraju.hpp"

#include <cstdio>
#include <utility>
#include <vector>

using VII = std::vector<std::pair<int,int>>;

namespace {

  int run_case(const char *name, int n,
      const VII &edges,
      int expected) {
    Kosaraju scc(n);
    for (const auto &e : edges) scc.add_edge(e.first, e.second);
    int got = scc.exec();
    if (got != expected) {
      std::printf("%s: expected %d, got %d\n", name, expected, got);
      return 1;
    }
    return 0;
  }

} // namespace

int main() {
  int failures = 0;

  failures += run_case("empty_graph", 0, {}, 0);

  failures += run_case("single_node", 1, {}, 1);

  for(int len = 1; len < 1024; ++len) {
    VII edges;
    for(int i = 0; i < len-1; ++i) edges.emplace_back(i, i+1);
    failures += run_case("linear_chain", len, edges, len);

    edges.emplace_back(len-1, 0);
    failures += run_case("cycle", len, edges, 1);
  }

  failures += run_case("two_components", 5,
      {{0, 1}, {1, 0},
      {2, 3}, {3, 4}, {4, 2}}, 2);

  // Common example used in SCC/Kosaraju explanations (GfG).
  failures += run_case("gfg_example", 5,
      {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}}, 3);

  // Two cycles linked in one direction, plus a 2-node SCC.
  failures += run_case("three_sccs", 8,
      {{0, 1}, {1, 2}, {2, 0},
      {2, 3}, {3, 4}, {4, 5}, {5, 3},
      {5, 6}, {6, 7}, {7, 6}}, 3);

  failures += run_case("user_graph", 8,
      {{0, 1}, {1, 3}, {3, 2}, {2, 1},
      {3, 4}, {4, 5}, {5, 7}, {7, 6}, {6, 4}}, 3);

  return failures;
}
