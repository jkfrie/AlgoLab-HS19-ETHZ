#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> > weighted_graph;

typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

int n, m;
edge_desc e;

int dijkstra_path(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int>         dist_map(n);
  std::vector<vertex_desc> pred_map(n);

  boost::dijkstra_shortest_paths(G, s,boost::distance_map(boost::make_iterator_property_map(
    dist_map.begin(), boost::get(boost::vertex_index, G)))
    /* dot! */ .predecessor_map(boost::make_iterator_property_map(
    pred_map.begin(), boost::get(boost::vertex_index, G))));

  int result = *max_element(dist_map.begin(), dist_map.end());
  return result;
}

int kruskal(const weighted_graph &G, weight_map weights) {
  std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  int cost = 0;
  for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    cost += weights[*it];
  }
  return cost;
}

void testcase() {
  // Set up Graph G
  std::cin >> n >> m;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  //cout << "n: " << n << " m: " << m << endl;
  int s, t, w;
  for (int i = 0; i < m; ++i) {
    std::cin >> s >> t >> w;
    e = boost::add_edge(s, t, G).first; weights[e]=w;
  }

  // Compute MST
  int cost = kruskal(G, weights);
  std::cout << cost << " ";

  // Compute Max Distance
  int maxDist = dijkstra_path(G, 0, 0);
  std::cout << maxDist << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
