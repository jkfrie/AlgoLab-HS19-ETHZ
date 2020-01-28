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

    void add_edge(int from, int to, long capacity) {
      auto c_map = get(edge_capacity, G);
      auto r_map = get(edge_reverse, G);
      const auto e = boost::add_edge(from, to, G).first;
      const auto rev_e = boost::add_edge(to, from, G).first;
      c_map[e] = capacity;
      c_map[rev_e] = 0; // reverse edge has no capacity!
      r_map[e] = rev_e;
      r_map[rev_e] = e;
    }
};

void testcase() {

  // Read Input
  int n, m;
  cin >> n >> m;

  // Setup Graph
  flow_graph G(n);
  edge_adder adder(G);

  const vertex_desc v_source = add_vertex(G);
  const vertex_desc v_target = add_vertex(G);

  // Setup edges from source
  int a, b, c;
  for(int i = 0; i < m; ++i) {
    cin >> a >> b >> c;

    if(c == 1)
      adder.add_edge(v_source, a, 1);
    else if(c == 2)
      adder.add_edge(v_source, b, 1);
    else {
      vertex_desc game = add_vertex(G);
      adder.add_edge(v_source, game, 1);
      adder.add_edge(game, a, 1);
      adder.add_edge(game, b, 1);
    }
  }

  // Setup edges to target
  int s;
  int scores = 0;
  for(int i = 0; i < n; ++i) {
    cin >> s;
    scores += s;
    adder.add_edge(i, v_target, s);
  }

  if(scores != m) {
    cout << "no" << endl;
    return;
  }

  // Calculate max flow
  long flow = boost::push_relabel_max_flow(G, v_source, v_target);

  // Output result
  if(flow == scores)
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
