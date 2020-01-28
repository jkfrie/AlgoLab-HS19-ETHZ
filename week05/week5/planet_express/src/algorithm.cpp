#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
#define REP(i, n) for(int i = 0; i < n; ++i)

// Graph Type, OutEdgeList Type, VertexList Type, (un)directedS
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void testcase() {
  int n, m, k, t; cin >> n >> m >> k >> t;
  vector<int> telnetwork(t);
  REP(i, t) cin >> telnetwork[i];

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;

  REP(i, m) {
    int u, v, c; cin >> u >> v >> c;
    e = boost::add_edge(v, u, G).first; weights[e]=c;
  }

  // find Teleportation routes and add them to G
  vector<int> scc_map(n);	// We MUST use such a vector as an Exterior Property Map: Vertex -> Component
  int nscc = boost::strong_components(G, boost::make_iterator_property_map(scc_map.begin(), boost::get(boost::vertex_index, G)));
  //cout << nscc << endl;

  vector<vector<int>> linked(nscc);
  for(auto elem : telnetwork) {
    linked[scc_map[elem]].push_back(elem);
  }

  REP(i, nscc) {
    vertex_desc teleporter = boost::add_vertex(G);
    for(auto telenode : linked[i]) {
      e = boost::add_edge(telenode, teleporter, G).first; weights[e]=linked[i].size() - 1;
      //cout << "add teleporter: " << telenode << " " << i << " " << weights[e] << endl;
      e = boost::add_edge(teleporter, telenode, G).first; weights[e]=0;
    }
  }

  // find closest storage house and dist
  int nodes = boost::num_vertices(G);
  std::vector<int>         dist_map(nodes);
  std::vector<vertex_desc> pred_map(nodes);

  boost::dijkstra_shortest_paths(G, n-1,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G)))
    .predecessor_map(boost::make_iterator_property_map(
      pred_map.begin(), boost::get(boost::vertex_index, G))));

  int min_dist = numeric_limits<int>::max();

  REP(i, k) {
    min_dist = min(min_dist, dist_map[i]);
    //cout << min_dist << endl;
  }

  if(min_dist < 1000000) cout << min_dist << endl;
  else cout << "no" << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
