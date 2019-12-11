#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

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

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  edge_desc add_edge(int from, int to, long capacity, long cost) {
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
    return e;
  }
};

void testcase() {

  // Read input
  int c, g, b, k, a; cin >> c >> g >> b >> k >> a;

  // construct graph and add edges
    graph G(c);
    int source = add_vertex(G);
  	int target = add_vertex(G);
    edge_adder adder(G);
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);
  REP(i, g) {
    int x, y, d, e; cin >> x >> y >> d >> e;
    adder.add_edge(x, y, e, d);
  }

  // Find maximum flow, this will be max nr of suitcases that are possible with
  // the given guides. By setting the capacity of the edges from source to Kholby
  // we can limit nr of suitcases. Use binary search to find maximum flow that is
  // below cost b.
  adder.add_edge(a, target, INT_MAX, 0);
  edge_desc e_src = adder.add_edge(source, k, INT_MAX, 0);
  // Min Cost Max Flow with successive_shortest_path_nonnegative_weights
  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  int cost = boost::find_flow_cost(G);
  // Iterate over all edges leaving the source to sum up the flow values.
  int max_flow = 0;
  out_edge_it e, eend;
  for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e) {
      max_flow += c_map[*e] - rc_map[*e];
  }
  if(cost < b) {
    cout << max_flow << endl;
    return;
  }

  int left = 0;
  int right = max_flow;
  int result = 0;
  //cout << "max-flow: " << max_flow << endl;
  int middle;
  while(left <= right) {
   // Adjust capacity of source - Kholby edge
   middle = (right + left) / 2;
   //cout << "middle: " << middle << endl;
   c_map[e_src] = middle;

   // Min Cost Max Flow with successive_shortest_path_nonnegative_weights
   boost::successive_shortest_path_nonnegative_weights(G, source, target);
   int cost = boost::find_flow_cost(G);
   // Iterate over all edges leaving the source to sum up the flow values.
   int flow = 0;
   out_edge_it e, eend;
   for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source,G), G); e != eend; ++e) {
       flow += c_map[*e] - rc_map[*e];
   }

   // If solution is too expensive
   if(cost > b ) {
      right = middle - 1;
      //cout << "right = " << right << endl;
   }
   else {
      left = middle + 1;
      result = max(result, flow);
      //cout << "left = " << left << endl;
   }
  }

  cout << result << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
