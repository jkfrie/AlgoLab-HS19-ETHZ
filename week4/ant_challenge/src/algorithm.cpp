#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > weighted_graph;
typedef property_map<weighted_graph, edge_weight_t>::type WeightMap;
typedef graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

int n, e, s, a ,b;
edge_desc cur_edge;
vector<edge_desc> mst;

int dijkstra_path(const weighted_graph &G, int source, int dest) {
  int n = num_vertices(G);
  vector<int>         dist_map(n);
  vector<vertex_desc> pred_map(n);

  dijkstra_shortest_paths(G, source,distance_map(make_iterator_property_map(
    dist_map.begin(), get(vertex_index, G))).predecessor_map(make_iterator_property_map(
      pred_map.begin(), get(vertex_index, G))));
  return dist_map[dest];
}

void kruskal(const weighted_graph &G) {
  kruskal_minimum_spanning_tree(G, back_inserter(mst));
  return;
}

void testcase() {
  std::cin >> n >> e >> s >> a >> b;
  vector<weighted_graph> species_graphs(s);
  vector<WeightMap> species_weights(s);

  // Init graphs
  for(int i = 0; i < s; ++i) {
    species_graphs[i] = weighted_graph(n);
    species_weights[i] = get(edge_weight, species_graphs[i]);
  }

  // Set up Graphs for insect networks and total graph
  weighted_graph total_graph(n);
  WeightMap weights_tg = get(edge_weight, total_graph);

  int source, dest, w;
  for (int i = 0; i < e; ++i) {
    cin >> source >> dest;
    for(int j = 0; j < s; ++j) {
      cin >> w;
      cur_edge = add_edge(source, dest, species_graphs[j]).first; species_weights[j][cur_edge]=w;
    }
    // Add edge to total graph and set weight to maxDist
    cur_edge = add_edge(source, dest, total_graph).first; weights_tg[cur_edge] = std::numeric_limits<int>::max();
  }

  // Compute MST of all species_graphs
  int hive;
  for (int i = 0; i < s; ++i) {
    cin >> hive;

    mst = vector<edge_desc>();
    kruskal(species_graphs[i]);

    // Loop over all edges in MST and adjust weigths of total graph if smaller
    int curWeight;
    for (auto elem : mst) {
      curWeight = species_weights[i][elem];

      vertex_desc u = boost::source(elem, species_graphs[i]);
      vertex_desc v = target(elem, species_graphs[i]);
      cur_edge = edge(u, v, total_graph).first;
      //cout << "found weight: " << elem << " : " << curWeight << " cur weight is: " << weights_tg[cur_edge] << endl;
      weights_tg[cur_edge] = min(weights_tg[cur_edge], curWeight);
    }
  }

  // Compute Min Distance
  int minDist = dijkstra_path(total_graph, a, b);
  cout << minDist << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
