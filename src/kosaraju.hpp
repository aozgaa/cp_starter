#pragma once

#include <vector>

using VI = std::vector<int>;
using VVI = std::vector<std::vector<int>>;

struct Kosaraju {
  enum { UNVISITED = 0, VISITED = 1 }; 

  Kosaraju(int n) : n_{n}, al_(n), alt_(n), dfs_vis_(n,0), s_{} {}

  void add_edge(int from, int to) {
    al_[from].push_back(to);
    alt_[to].push_back(from);
  }

  int exec() {
    s_.clear();
    dfs_vis_.assign(n_, UNVISITED);
    for(int u = 0; u < n_; ++u)
      if(!dfs_vis_[u]) do_pass(u, false);
    dfs_vis_.assign(n_, UNVISITED);
    int res = 0;
    for(int i = n_ - 1; i >= 0; --i)
      if(dfs_vis_[s_[i]] == UNVISITED) ++res, do_pass(s_[i], true);
    return res;
  }

  private:
    int n_;
    VVI al_;
    VVI alt_;
    VI dfs_vis_;
    VI s_;
    
  void do_pass(int u, bool is_rev) {
    dfs_vis_[u] = VISITED;
    auto &nbrs = is_rev ? alt_[u] : al_[u];
    for(auto n : nbrs) if(dfs_vis_[n] == UNVISITED) do_pass(n, is_rev);
    if (!is_rev) s_.push_back(u);
  }
};
