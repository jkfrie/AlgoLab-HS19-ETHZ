#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::graph_traits<weighted_graph>::out_edge_iterator          out_edge_it;
typedef boost::graph_traits<weighted_graph>::edge_iterator              edge_it;

#define REP(i, n) for(int i = 0; i < n; ++i)

using namespace std;

void testcase() {
  // Read input
  int n, first_planet; cin >> n >> first_planet;

  // Make graph
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  REP(i, n) {
    for(int j = i + 1; j < n; ++j) {
      edge_desc e;
      e = boost::add_edge(i, j, G).first;
      cin >> weights[e];
    }
  }

  // Compute Kruskal MST, because we only care about the total weight of taken
  // edges kruskal is identical to Prim
  std::vector<edge_desc> mst; // vector to store MST edges (not a property map!)
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

  // Create a Graph = MST
  int total_cost = 0;
  weighted_graph MST(n);
  weight_map weights_mst = boost::get(boost::edge_weight, MST);
  vector<vector<bool>> edge_taken(n, vector<bool>(n, false));
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    edge_desc e;
    e = boost::add_edge(boost::source(*it, G), boost::target(*it, G), MST).first;
    weights_mst[e] = weights[*it];
    total_cost += weights[*it];
    // Add an entry to mark this edge as taken in MST
    edge_taken[boost::source(*it, G)][boost::target(*it, G)] = true;
    edge_taken[boost::target(*it, G)][boost::source(*it, G)] = true;
  }


  //****************************************************************************
  // Slower Approach: For each edge that is taken in MST adjust weights to inf
  //    and compute MST again. Then take the MST that is minimal from all the
  //    MST's where we set one edge to inf.
  // Fast Approach: For each edge in normal Graph G that is not in MST, add it.
  //    Now MST has a cycle -> delete edge with max weight in cycle (except
  //    added edge)
  //****************************************************************************

  // Loop over all possible edges (u,v) of G and compute max weight of any edge in
  // Cycle if we would add (u,v) to the MST graph. Use BFS to find v from u and compute max weight in the path to v.
  vector<vector<int>> max_weight_cycle(n, vector<int>(n, 0));
  REP(i, n) {

    // BFS for node i as src
    vector<bool> visited(n, false);
    queue<int> q;
    visited[i] = true;
    q.push(i);
    while(!q.empty()) {
      int cur_node = q.front(); q.pop();
      out_edge_it oe_beg, oe_end;

      // Iterate over neighbors
      for (boost::tie(oe_beg, oe_end) = boost::out_edges(cur_node, MST); oe_beg != oe_end; ++oe_beg) {
        assert(boost::source(*oe_beg, MST) == cur_node);
        int next_node = boost::target(*oe_beg, MST);
        if(!visited[next_node]) {
          max_weight_cycle[i][next_node] = max(max_weight_cycle[i][cur_node], weights_mst[*oe_beg]);
          visited[next_node] = true;
          q.push(next_node);
        }
      }
    }
  }

  // compute cost increase to normal MST -> for each pair (u,v):
  // weight[edge(u,v)] - max_weight_cycle[u][v]
  edge_it e_beg, e_end;
  int min_cost = INT_MAX;
  for (boost::tie(e_beg, e_end) = boost::edges(G); e_beg != e_end; ++e_beg) {
    if(!edge_taken[boost::source(*e_beg, G)][boost::target(*e_beg, G)]) {
      int cost = weights[*e_beg] - max_weight_cycle[boost::source(*e_beg, G)][boost::target(*e_beg, G)];
      min_cost = min(cost, min_cost);
    }
  }

  // Output result
  cout << total_cost + min_cost << endl;

}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
