#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <stdexcept>
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

  int n, m; cin >> n >> m;
  // Create graph, edge adder class and propery maps
  graph G(n);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto r_map = boost::get(boost::edge_reverse, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);
  int v_source = boost::add_vertex(G);
  int v_target = boost::add_vertex(G);

  REP(i, n-1) {
    int c; cin >> c;
    adder.add_edge(i, i+1, c, 0);
    //adder.add_edge(v_source, i, c, 0);
    //adder.add_edge(i + 1, v_target, c, 0);
  }

  REP(i, m) {
    int a, b, d; cin >> a >> b >> d;
    adder.add_edge(v_source, a, 1, 0);
    adder.add_edge(b, v_target, 1, 128 - d);
  }

  // Run the algorithm
  // Option 2: Min Cost Max Flow with
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

  cout << s_flow * 128 - cost2 << endl;
  return;
}

int main(int argc, char const *argv[]) {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) testcase();
}
