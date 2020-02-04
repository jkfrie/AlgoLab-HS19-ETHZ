#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/find_flow_cost.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>

using namespace std;

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS>
    traits;
typedef boost::adjacency_list<
    boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<
        boost::edge_capacity_t, long,
        boost::property<
            boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                            boost::property<boost::edge_weight_t, long> > > > >
    graph;  // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator out_edge_it;  // Iterator

#define REP(i, n) for (int i = 0; i < n; ++i)

// Custom edge adder class
class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G);  // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0;  // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;       // new assign cost
    w_map[rev_e] = -cost;  // new negative cost
  }
};

void testcase() {
  int c, g, b, k, a;
  cin >> c >> g >> b >> k >> a;
  int N = c;

  // Create graph, edge adder class and propery maps
  graph G(N);
  graph Ginit(N);
  edge_adder adder(G);
  edge_adder adder_init(Ginit);

  // Add the edges
  int max_suitcases = 0;
  REP(i, g) {
    int x, y, d, e;
    cin >> x >> y >> d >> e;
    adder.add_edge(x, y, e, d);
    adder_init.add_edge(x, y, e, d);
  }

  // Find max_flow to get max nr of suitcases!
  auto c_map = boost::get(boost::edge_capacity, Ginit);
  auto r_map = boost::get(boost::edge_reverse, Ginit);
  auto rc_map = boost::get(boost::edge_residual_capacity, Ginit);
  boost::successive_shortest_path_nonnegative_weights(Ginit, k, a);
  // Iterate over all edges leaving the source to sum up the flow values.
  int init_flow = 0;
  out_edge_it e, eend;
  for (boost::tie(e, eend) = boost::out_edges(boost::vertex(k, Ginit), Ginit);
       e != eend; ++e) {
    init_flow += c_map[*e] - rc_map[*e];
  }

  // find nr of suitcases with binary search where cost is not above b
  int v_source = boost::add_vertex(G);
  int v_target = a;
  int prev_max = 0;
  adder.add_edge(v_source, k, 0, 0);

  int l = 0;
  int r = init_flow;
  while (l <= r) {
    int m = l + (r - l) / 2;

    auto c_map = boost::get(boost::edge_capacity, Ginit);
    auto r_map = boost::get(boost::edge_reverse, Ginit);
    auto rc_map = boost::get(boost::edge_residual_capacity, Ginit);

	// set capacity of edge from src to m;
	c_map[boost::edge(v_source, k, G).first] = m;

	// successive_shortest_path_nonnegative_weights
    boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
    int cost2 = boost::find_flow_cost(G);
    // Iterate over all edges leaving the source to sum up the flow values.
    int s_flow = 0;
    out_edge_it e, eend;
    for (boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source, G), G);
         e != eend; ++e) {
      s_flow += c_map[*e] - rc_map[*e];
    }

    // If x greater, ignore left half
    if (cost2 <= b) l = m + 1;

    // If x is smaller, ignore right half
    else
      r = m - 1;
  }

  cout << l - 1 << "\n";
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) testcase();
}
