#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

// Includes
// ========
#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

#define REP(i, n) for (int i = 0; i < (n); ++i)

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

void testcase() {
  int n; cin >> n;
  const int N= n + 2;
  const int v_source = N - 2;
  const int v_target = N - 1;

  // Create graph, edge adder class and propery maps
  graph G(N);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);

  // Add the edges
  // Add menues per day
  REP(i, n) {
    int a, c; cin >> a >> c;
    adder.add_edge(v_source, i, a, c);
  }

  // Add students eating per day
  int total_students = 0;
  REP(i, n) {
    int s, p; cin >> s >> p;
    total_students += s;
    adder.add_edge(i, v_target, s, 20 - p);
  }

  // Add possibility to refrigerate
  REP(i, n - 1) {
    int v, e; cin >> v >> e;
    adder.add_edge(i, i + 1, v, e);
  }

  // Run the algorithm
  // Option 2: Min Cost Max Flow with successive_shortest_path_nonnegative_weights
  boost::successive_shortest_path_nonnegative_weights(G, v_source, v_target);
  int cost1 = boost::find_flow_cost(G);
  // Iterate over all edges leaving the source to sum up the flow values.
  int flow1 = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_source,G), G); e != eend; ++e) {
    flow1 += c_map[*e] - rc_map[*e];
  }

  // Output Result
  if(flow1 >= total_students)
    cout << "possible ";
  else
    cout << "impossible ";
  std::cout << flow1 << " ";
  std::cout << 20 * flow1 -cost1 << "\n";

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
