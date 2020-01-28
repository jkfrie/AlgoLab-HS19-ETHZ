#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <unordered_map>
#include <stdexcept>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define ST first
#define ND second

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
  int h, w; cin >> h >> w;
  string note; cin >> note;
  //cout << "h: " << h << ", w: " << w << endl;

  std::unordered_map<int, int> letters;
  int n = 0;
  int cur;
  for(char c : note) {
    //cout << "char " << c << endl;
    cur = (int) c - (int) 'A';
    ++letters[cur];
    ++n;
  }

  // Setup Graph
  flow_graph G(26);
  edge_adder adder(G);

  const vertex_desc source = boost::add_vertex(G);
  const vertex_desc target = boost::add_vertex(G);

  vector<int> front(h*w);
  vector<int> back(h*w);
  int offset = (int) 'A';
  char c;

  // Read in letters from front
  REP(i, h){
    REP(j, w) {
      cin >> c;
      front[i*w + j] = int(c) - offset;
    }
  }
  // Read in letters from back
  REP(i,h) {
    REP(j,w) {
      cin >> c;
      back[i*w + (w-j-1)] = int(c) - offset;
    }
  }

  // find all unique pairs of letters of front and back
  vector<vector<int>> pairs(26, vector<int>(26, 0));
  REP(i, h*w) {
    ++pairs[front[i]][back[i]];
  }

  // Add edges to Graph from source
  vertex_desc pair;
  REP(i, 26) {
    REP(j, 26) {
      pair = boost::add_vertex(G);
      adder.add_edge(source, pair, pairs[i][j]);
      adder.add_edge(pair, i, pairs[i][j]);
      adder.add_edge(pair, j, pairs[i][j]);
    }
  }

  // Add edges to target
  for(auto elem : letters) {
    adder.add_edge(elem.ST, target, elem.ND);
  }

  // Calculate max flow
  long flow = boost::push_relabel_max_flow(G, source, target);

  // Output result
  //cout << flow << endl;
  if(flow == n)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
