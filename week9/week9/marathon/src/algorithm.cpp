#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property,
                              boost::property<boost::edge_weight_t, int,
							  boost::property<boost::edge_capacity_t, long>>>
    weighted_graph;
typedef boost::graph_traits<weighted_graph>::edge_iterator edge_it;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type
    weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>
    traits;
typedef boost::adjacency_list<
    boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
                    boost::property<boost::edge_residual_capacity_t, long,
                                    boost::property<boost::edge_reverse_t,
                                                    traits::edge_descriptor>>>>
    graph;

#define REP(i, n) for (int i = 0; i < n; ++i)

// Custom edge adder class, highly recommended
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;  // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase() {
  int n, m, s, f;
  cin >> n >> m >> s >> f;
  weighted_graph G(n);
  auto weights = boost::get(boost::edge_weight, G);
  auto capacities = boost::get(boost::edge_capacity, G);

  REP(i, m) {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    edge_desc e = boost::add_edge(a, b, G).first;
    weights[e] = d;
	capacities[e] = c;
  }

  // find distances from finish and from start for all intersections
  std::vector<int> f_dist_map(n);
  boost::dijkstra_shortest_paths(
      G, f,
      boost::distance_map(boost::make_iterator_property_map(
          f_dist_map.begin(), boost::get(boost::vertex_index, G))));

  std::vector<int> s_dist_map(n);
  boost::dijkstra_shortest_paths(
      G, s,
      boost::distance_map(boost::make_iterator_property_map(
          s_dist_map.begin(), boost::get(boost::vertex_index, G))));

  const int shortest_path = s_dist_map[f];
  //cout << "shortest_path: " << shortest_path << endl;

  // add all legal streets to a new flowgraph
  graph flow_graph(n);
  edge_adder adder(flow_graph);

  edge_it e_beg, e_end;
  for (boost::tie(e_beg, e_end) = boost::edges(G); e_beg != e_end; ++e_beg) {
    //std::cout << boost::source(*e_beg, G) << " " << boost::target(*e_beg, G)
    //          << "\n";

    int u = boost::source(*e_beg, G);
    int v = boost::target(*e_beg, G);

    if (s_dist_map[u] > s_dist_map[v]) swap(u, v);

    // Check if on a shortest path
    //cout << "edge: " << u << " " << v << "\n";
    //cout << s_dist_map[u] << " " << weights[*e_beg] << " " << f_dist_map[v]
    //     << "\n";
    if (s_dist_map[u] + weights[*e_beg] + f_dist_map[v] == shortest_path) {
      adder.add_edge(u, v, capacities[*e_beg]);
      //cout << "add_edge: " << u << " " << v << " " << weights[*e_beg] << endl;
    }
  }

  // Calculate maxflow from source to sink
  long flow = boost::push_relabel_max_flow(flow_graph, s, f);
  std::cout << flow << "\n";
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) testcase();
}
