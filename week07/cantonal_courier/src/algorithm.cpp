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

#define REP(i, n) for(int i = 0; i < n; ++i)

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
  int z, j;
  cin >> z >> j;

  // Setup Graph
  flow_graph G(z + j);
  edge_adder adder(G);

  int source = add_vertex(G);
	int target = add_vertex(G);

  // Add edges from zones to targets
  int cost;
  REP(i, z){
    cin >> cost;
    adder.add_edge(j + i, target, cost);
    //cout << "add: " << j + i << ", target" << " " << cost << endl;
  }

  // Add edges from source to jobs
  int price;
  int total_price = 0;
  REP(i, j){
    cin >> price;
    total_price += price;
    adder.add_edge(source, i, price);
    //cout << "add: source " << i << " " << price << endl;
  }

  // Add edges between jobs and zones
  int n;
  int zone;
  REP(i, j) {
    cin >> n;
    REP(k, n) {
      cin >> zone;
      adder.add_edge(i, j + zone, INT_MAX);
      //cout << "add: " << i << ", " << j+zone << " max" << endl;
    }
  }

  // Calculate min cut = max flow
  long flow = boost::push_relabel_max_flow(G, source, target);

  // Output result
  //cout << "Total_price: " << total_price << " flow: " << flow << endl;
  cout << total_price - flow << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
