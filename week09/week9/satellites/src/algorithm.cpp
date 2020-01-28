#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

// Graph Type with nested interior edge properties for Flow Algorithms
typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >	graph;
// Interior Property Maps
typedef	boost::graph_traits<graph>::edge_descriptor			edge_desc;
typedef	boost::graph_traits<graph>::out_edge_iterator			out_edge_it;

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

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
	int g, s, l; cin >> g >> s >> l;

	// build graph
	const int N = g+s;
	graph G(N);
	edge_adder adder(G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);

	int src = boost::add_vertex(G);
	int sink = boost::add_vertex(G);

	// add links
	REP(i, l) {
		int u, v; cin >> u >> v;
		adder.add_edge(u, g + v, 1);
	}

	// add edges from src and to sink
	REP(i, g) adder.add_edge(src, i, 1);
	REP(i, s) adder.add_edge(g + i, sink, 1);

	// Find a min cut via maxflow
	int flow = boost::push_relabel_max_flow(G, src, sink);
	//std::cout << "maximum flow = minimum cut = " << flow << "\n";

	// BFS to find vertex set S
	std::vector<int> vis(N + 2, false); // visited flags
	std::queue<int> Q; // BFS queue (from std:: not boost::)
	vis[src] = true; // Mark the source as visited
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
			Q.push(v);
		}
	}

	// Output MinVC
	int counter = 0;
	vector<int> result;

	REP(i, g) {
		if(!vis[i]) {
			counter++;
			result.push_back(i);
		}
	}
	cout << counter << " ";
	counter = 0;
	REP(i, s) {
		if(vis[g + i]) {
			counter++;
			result.push_back(i);
		}
	}
	cout << counter << "\n";
	if(result.size() > 0) {
		for(auto elem : result) {
		cout << elem << " ";
		}
		cout << "\n";
	}
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
