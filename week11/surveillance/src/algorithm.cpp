#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

// BGL include
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

#define REP(i, n) for(int i = 0; i < n; ++i)

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
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase() {
  // Read input
  int n, m, k, l; cin >> n >> m >> k >> l;

  // Make graph that has streetnetwork stored twice once with unlimited capacities
  // (to demonstrate constraint for policeman without photograph)and once with
  // capacity 1 for each street (to demonstrate constraints for policeman with photograph)
  graph G(2 * n);
  edge_adder adder(G);
  // Add special vertices source and sink
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  // Add edge to target from each police station of second streetnetwork
  // Add edge from src to each police station in first streetnetwork
  REP(i, k) {
    int x; cin >> x;
    adder.add_edge(x + n, v_target, 1);
    adder.add_edge(v_source, x, 1);
  }

  // for every photograph add connection between two streetnetworks
  REP(i, l) {
    int x; cin >> x;
    adder.add_edge(x, x + n, 1);
  }

  // Add edge for each street in both networks
  REP(i, m) {
    int x, y; cin >> x >> y;
    adder.add_edge(x, y, INT_MAX);
    adder.add_edge(x + n, y + n, 1);
  }

  // Calculate flow from source to sin
  long flow = boost::push_relabel_max_flow(G, v_source, v_target);
  std::cout << flow << "\n";


}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
