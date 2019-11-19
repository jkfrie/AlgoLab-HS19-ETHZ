#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <map>

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
#include <boost/graph/dijkstra_shortest_paths.hpp>

// Typedefs for first graph
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,		// Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
		boost::no_property,				// interior properties of vertices
    boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_weight_t, int> > >			 graph1;
typedef boost::graph_traits<graph1>::edge_descriptor		   edge_desc1;		// Edge Descriptor: an object that represents a single edge.
typedef boost::graph_traits<graph1>::vertex_descriptor		 vertex_desc1;		// Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).
typedef boost::graph_traits<graph1>::edge_iterator		     edge_it1;		// to iterate over all edges

// Typedefs for second graph
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_iterator               edge_it;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;
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
  int n, m, s, f; cin >> n >> m >> s >> f;

  // Create graph for applying dijkstra
  graph1 G_dist(n);
  edge_desc1 e;
  auto weights = boost::get(boost::edge_weight, G_dist);
  auto capacities = boost::get(boost::edge_capacity, G_dist);

  // Add the edges
  REP(i, m) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    e = boost::add_edge(a, b, G_dist).first; weights[e]=d; capacities[e]=c;
  }

  // Find shortest path from start
  std::vector<int> dist_map_s(n);
  boost::dijkstra_shortest_paths(G_dist, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map_s.begin(), boost::get(boost::vertex_index, G_dist))));

  // Find shortest path from finish
  std::vector<int> dist_map_f(n);
  boost::dijkstra_shortest_paths(G_dist, f,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map_f.begin(), boost::get(boost::vertex_index, G_dist))));

  // Loop over all edges of Graph and check if part of a shortest path
  // if so add to new flow graph G
  graph G(n);
  edge_adder adder(G);
  auto c_map = capacities;
  auto w_map = weights;
  const int path_length = dist_map_s[f];
  //cout << "path length: " << path_length;

  edge_it1 ebeg, eend;
  for (boost::tie(ebeg, eend) = boost::edges(G_dist); ebeg != eend; ++ebeg) {
    int u = boost::source(*ebeg, G_dist), v = boost::target(*ebeg, G_dist);
    int length = w_map[*ebeg];
    int capacity = c_map[*ebeg];

    // if u closer to start then v
    if(dist_map_s[u] < dist_map_s[v]) {
      if(dist_map_s[u] + length + dist_map_f[v] == path_length) {
        adder.add_edge(u, v, capacity, 0);
        //cout << "add edge: " << u << " " << v << " " << capacity << endl;
      }
    }

    // if v closer to start then u
    if(dist_map_s[v] < dist_map_s[u]) {
      if(dist_map_s[v] + length + dist_map_f[u] == path_length) {
        adder.add_edge(v, u, capacity, 0);
        //cout << "add edge: " << v << " " << u << " " << capacity << endl;
      }
    }
  }

  // Run the algorithm
  long flow = boost::push_relabel_max_flow(G, s, f);

  // Output Result
  std::cout << flow << "\n";

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
