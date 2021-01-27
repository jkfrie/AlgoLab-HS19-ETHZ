#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
// BGL include
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/connected_components.hpp>

using namespace std;

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

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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
  int n, m, k, l; cin >> n >> m >> k >> l;
  graph G(2*n);
  edge_adder adder(G);

  int v_source = boost::add_vertex(G);
  int v_target = boost:: add_vertex(G);

  // add edge from station to target
  REP(i, k) {
	  int p; cin >> p;
	  adder.add_edge(n + p, v_target, 1);
	  adder.add_edge(v_source, p, 1);
  }

  // add edge from src to photo
  REP(i, l) {
	  int p; cin >> p;
	  adder.add_edge(p, n + p, 1);
  }

  // add street network
  REP(i, m) {
	  int x, y; cin >> x >> y;
	  adder.add_edge(x, y, INT_MAX);
	  adder.add_edge(n + x, n + y, 1);
  }

  // Calculate flow from source to sink
  long flow = boost::push_relabel_max_flow(G, v_source, v_target);
  std::cout << flow << "\n";

  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) testcase();
}
