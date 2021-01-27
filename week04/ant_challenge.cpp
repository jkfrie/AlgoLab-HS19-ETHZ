#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
  int n, e, s, a, b; cin >> n >> e >> s >> a >> b;

  // Init the network graphs of each species and a graph that will combine
  //best of all species
  vector<weighted_graph> networks;
  vector<weight_map> network_weights;
  REP(i, s) {
    weighted_graph G(n);
    networks.push_back(G);
    network_weights.push_back(boost::get(boost::edge_weight, G));
  }

  // Setup edges of network graphs
  REP(i, e) {
    int t1, t2; cin >> t1 >> t2;
    REP(j, s) {
      int w; cin >> w;
      edge_desc e;
      e = boost::add_edge(t1, t2, networks[j]).first; network_weights[j][e]=w;
    }
  }

  REP(i, s) {int h; cin >> h;}

  // Find min spanning tree for each network graph -> network
  vector<vector<int>> min_weights(n, vector<int>(n, numeric_limits<int>::max()));
  REP(i, s) {
    std::vector<edge_desc> mst;    // vector to store MST edges (not a property map!)
    boost::kruskal_minimum_spanning_tree(networks[i], std::back_inserter(mst));
    // adjust weights of forest where weights of species network are smaller
    for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
      int src = boost::source(*it, networks[i]);
      int tar = boost::target(*it, networks[i]);
      //cout << src << " " << tar << endl;
      min_weights[src][tar] = min(min_weights[src][tar], network_weights[i][*it]);
    }
  }

  // Create graph to simulate forest with all species
  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  REP(i, n) {
    REP(j, n) {
      edge_desc e;
      if(min_weights[i][j] < numeric_limits<int>::max()) {
        e = boost::add_edge(i, j, G).first; weights[e]=min_weights[i][j];
      }
    }
  }

  // Perform Dijkstra to find shortest path from a to b
  std::vector<int>         dist_map(n);
  std::vector<vertex_desc> pred_map(n);

  boost::dijkstra_shortest_paths(G, a,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G)))
    .predecessor_map(boost::make_iterator_property_map(
      pred_map.begin(), boost::get(boost::vertex_index, G))));

  cout << dist_map[b] << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
