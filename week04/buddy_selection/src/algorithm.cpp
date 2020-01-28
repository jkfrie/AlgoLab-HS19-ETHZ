#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <set>
#include <unordered_set>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > weighted_graph;
typedef property_map<weighted_graph, edge_weight_t>::type WeightMap;
typedef graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

typedef vector<std::unordered_set<std::string>> VSS;
typedef vector<int> VI;

edge_desc cur_edge;

void testcase() {
  int n, c, f;
  std::cin >> n >> c >> f;

  // Init Graphs and Vector of Sets of Charachteristics
  weighted_graph relation_graph = weighted_graph(n);
  WeightMap weights = get(edge_weight, relation_graph);
  VSS characteristics = VSS(n);
  VI curWeights;


  // Read in Charachteristics and Fill edges of Graph
  string curCharacteristic;
  for (int i = 0; i < n; ++i) {

    // Rad in Charachteristics and store in sorted Set
    curWeights = VI(i, 0);
    for(int j = 0; j < c; ++j) {
      cin >> curCharacteristic;
      characteristics[i].insert(curCharacteristic);

      // Adjust weights of edges to insert
      for(int k = 0; k < i; ++k) {
        if(characteristics[k].find(curCharacteristic) != characteristics[k].end()) {
          ++curWeights[k];
        }
      }

      // Add edges to current student to relation_graph
      for(int k = 0; k < i; ++k) {
        if(curWeights[k] > f) {
          cur_edge = add_edge(i, k, relation_graph).first; weights[cur_edge] = curWeights[k];
        }
      }
    }
  }

  // Compute Maximum Matching of realation_graph
  vector<vertex_desc> mate_map(n);  // exterior property map
  const vertex_desc NULL_VERTEX = graph_traits<weighted_graph>::null_vertex();
  edmonds_maximum_cardinality_matching(relation_graph,make_iterator_property_map(mate_map.begin(), get(vertex_index, relation_graph)));
  int matching_size = boost::matching_size(relation_graph, make_iterator_property_map(mate_map.begin(), get(vertex_index, relation_graph)));

  // Output result
  if (matching_size * 2 == n) {
    cout << "not optimal" << endl;
  }
  else {
    cout << "optimal" << endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
