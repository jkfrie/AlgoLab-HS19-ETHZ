#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

// Graph Type with nested interior edge properties for flow algorithms
typedef adjacency_list_traits<vecS, vecS, directedS> traits;
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_capacity_t,
        long, property<edge_residual_capacity_t, long, property<edge_reverse_t,
        traits::edge_descriptor>>>> flow_graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
    flow_graph &G;

  public:
    explicit edge_adder(flow_graph &G) : G(G) {}

    edge_desc add_edge(int from, int to, long capacity) {
      auto c_map = get(edge_capacity, G);
      auto r_map = get(edge_reverse, G);
      const auto e = boost::add_edge(from, to, G).first;
      const auto rev_e = boost::add_edge(to, from, G).first;
      c_map[e] = capacity;
      c_map[rev_e] = 0; // reverse edge has no capacity!
      r_map[e] = rev_e;
      r_map[rev_e] = e;
      return e;
    }
};

void testcase() {

  // Read Input
  int n, m, s;
  cin >> n >> m >> s;

  // Setup Graph
  flow_graph G(n);
  edge_adder adder(G);
  const vertex_desc v_source = add_vertex(G);
  const vertex_desc v_target = add_vertex(G);

  // Setup edges to target
  int store;
  for(int i = 0; i < s; ++i) {
    cin >> store;
    adder.add_edge(store, v_target, 1);
  }

  // Setup streets
  int u, v;
  for(int i = 0; i < m; ++i) {
    cin >> u >> v;
    adder.add_edge(u, v, 1);
    adder.add_edge(v, u, 1);
  }


  // Calculate max flow
  long flow = boost::push_relabel_max_flow(G, 0, v_target);

  // Output result
  if(flow == s)
    cout << "yes" << endl;
  else
    cout << "no" << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
