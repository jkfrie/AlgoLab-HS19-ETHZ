#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;

// BGL graph definitions
// =====================
// Graph Type with nested interior edge properties for Flow Algorithms
typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >	graph;
// Interior Property Maps
typedef	boost::graph_traits<graph>::edge_descriptor			edge_desc;
typedef	boost::graph_traits<graph>::out_edge_iterator			out_edge_it;

#define REP(i, n) for (int i = 0; i < (n); ++i)

// Custom Edge Adder Class, that holds the references
// to the graph, capacity map and reverse edge map
// ===================================================
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase() {
  // read input
  int n, m; cin >> n >> m;

  // build graph
	const int N = n;
	graph G(N);
	edge_adder adder(G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);

	// add edges to Graph
  int a, b, c;
  REP(i, m) {
    cin >> a >> b >> c;
    adder.add_edge(a, b, c);
  }


	// Find a minimal min cut for all sources and sinks via maxflow
  int src, sink;
  int flow = INT_MAX;
  for(int i = 1; i < n; ++i) {
    int cur_flow1 = boost::push_relabel_max_flow(G, 0, i);
    if(cur_flow1 < flow) {
      flow = cur_flow1; src = 0; sink = i;
    }
    int cur_flow2 = boost::push_relabel_max_flow(G, i, 0);
    if(cur_flow2 < flow) {
      flow = cur_flow2; src = i; sink = 0;
    }
  }

	// BFS to find vertex set S
  flow = boost::push_relabel_max_flow(G, src, sink);
  vector<int> solution_set;
	std::vector<int> vis(N, false); // visited flags
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	vis[src] = true; // Mark the source as visited
  solution_set.push_back(src);
	Q.push(src);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		out_edge_it ebeg, eend;
		for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = boost::target(*ebeg, G);
			// Only follow edges with spare capacity
			if (rc_map[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
      solution_set.push_back(v);
			Q.push(v);
		}
	}

	// Output Result
  cout << flow << endl;
  cout << solution_set.size();
  sort(solution_set.begin(), solution_set.end());
  for(auto elem : solution_set) {
    cout << " " << elem;
  }
  cout << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
