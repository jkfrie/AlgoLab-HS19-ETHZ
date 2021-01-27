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
    int w, n; cin >> w >> n;

    graph G(2*(w+1));
    edge_adder adder(G);

    // limit number of cracks on each coordinate with simulated node capacities
    for(int i = 1; i < w; ++i) {
      adder.add_edge(2*i, 2*i + 1, 1);
    }
    adder.add_edge(0, 1, numeric_limits<int>::max());
    adder.add_edge(2*w, 2*w + 1, numeric_limits<int>::max());

    // connect brick edge points with an edge of capacity = 1;
    REP(i, n) {
      int u, v; cin >> u >> v;
      if(v < u) swap(u, v);
      adder.add_edge(2*u + 1, 2*v, 1);
    }

    // calculate push_relabel_max_flow
    long flow = boost::push_relabel_max_flow(G, 1, 2*w);
    std::cout << flow << "\n";
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
