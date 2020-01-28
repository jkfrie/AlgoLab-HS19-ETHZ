#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <unordered_set>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
  int n, c, f; cin >> n >> c >> f;

  vector<unordered_set<string>> characs(n);
  REP(i, n) {
    REP(j, c) {
      string c; cin >> c;
      characs[i].insert(c);
    }
  }

  graph G(n);

  REP(i, n) {
    for(int j = i; j < n; ++j) {
      if(i != j) {
        int sum = 0;
        for(auto elem : characs[i]) {
          if (characs[j].find(elem) != characs[j].end()) sum++;
        }
        if(sum > f) {
          //cout << "add_edge: " << i << " " << j << " " << sum << endl;
          boost::add_edge(i, j, G);
        }
      }
    }
  }

  // Maximum matching
  std::vector<vertex_desc> mate_map(n);  // exterior property map
  const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  if(matching_size * 2 == n) cout << "not optimal" << endl;
  else cout << "optimal" << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
