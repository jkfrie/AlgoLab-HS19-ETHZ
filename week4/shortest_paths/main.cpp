#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> > weighted_graph;

typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;
typedef vector<pair<int, int>> VII;

int n, m, q;
edge_desc e;

int dijkstra_path(const weighted_graph &G, int s, int t) {
  int n = boost::num_vertices(G);
  std::vector<int>         dist_map(n);
  std::vector<vertex_desc> pred_map(n);

  boost::dijkstra_shortest_paths(G, s,boost::distance_map(boost::make_iterator_property_map(
    dist_map.begin(), boost::get(boost::vertex_index, G)))
    /* dot! */ .predecessor_map(boost::make_iterator_property_map(
    pred_map.begin(), boost::get(boost::vertex_index, G))));

  int result = dist_map[t];
  return result;
}

void testcase() {
  // Set up Graph G
  std::cin >> n >> m >> q;
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  // Set up Vertex Locations
  VII locations = VII(n);
  for(int i = 0; i < n; ++i) {
    int lon, lat;
    cin >> lon >> lat;
    locations[i] = make_pair(lon, lat);
  }

  // Set up Edges
  int s, t, w;
  for (int i = 0; i < m; ++i) {
    std::cin >> s >> t >> w;
    e = boost::add_edge(s, t, G).first; weights[e]=w;
  }

  // Set up queries
  VII queries = VII(n);
  for(int i = 0; i < q; ++i) {
    cin >> s >> t;
    queries[i] = make_pair(s, t);
  }

  // Compute Distance for Queries
  int curDist;
  for(int i = 0; i < q; ++i) {
    curDist = dijkstra_path(G, queries[i].first, queries[i].second);
    if(curDist == std::numeric_limits<int>::max())
      cout << "unreachable" << endl;
    else
      cout << curDist << endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  testcase();
}
