#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <string>
// BGL include
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
#define REP(i, n) for(int i = 0; i < n; ++i)

// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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

  // Read and preprocess Input
  int h, w; cin >> h >> w;
  string note; cin >> note;
  int n = note.size();

  vector<int> note_letters(26, 0);
  for(auto ch : note) note_letters[((int) ch - (int) 'A')]++;

  vector<int> front(h*w);
  REP(i, h*w) {
    char c; cin >> c;
    front[i] = (int) c - (int) 'A';
  }

  vector<vector<int>> pairs(26, vector<int>(26, 0));
  REP(i, h) {
    for(int j = w-1; j >= 0; --j) {
      char c; cin >> c;
      pairs[front[i*w + j]][(int) c - (int) 'A'] += 1;
    }
  }

  // Setup a connection in from source to front letter to back letter and then
  // from each letter to sink if it is part of note.
  graph G(26);
  edge_adder adder(G);
  const vertex_desc v_source = boost::add_vertex(G);
  const vertex_desc v_target = boost::add_vertex(G);

  REP(i, 26) {
    REP(j, 26) {
      adder.add_edge(v_source, i, pairs[i][j]);
      adder.add_edge(i, j, pairs[i][j]);
    }
  }

  REP(i, 26) {
    adder.add_edge(i, v_target, note_letters[i]);
  }

  // Compute flow and output result
  long flow = boost::push_relabel_max_flow(G, v_source, v_target);
  if(flow==n) cout << "Yes" << "\n";
  else cout << "No" << "\n";

}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
