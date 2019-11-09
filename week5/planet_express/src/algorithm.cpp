#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/strong_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > weighted_graph;
typedef property_map<weighted_graph, edge_weight_t>::type WeightMap;
typedef graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef graph_traits<weighted_graph>::edge_iterator edge_it;
typedef graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

int n, m, k, t;
edge_desc cur_edge;

int dijkstra_path(const weighted_graph &G, int source, int dest) {
  int n = num_vertices(G);
  vector<int>         dist_map(n);
  vector<vertex_desc> pred_map(n);

  dijkstra_shortest_paths(G, source,distance_map(make_iterator_property_map(
    dist_map.begin(), get(vertex_index, G))).predecessor_map(make_iterator_property_map(
      pred_map.begin(), get(vertex_index, G))));

  // Find shortest distance to warehouse
  int min_dist = -1;
  for(int i = 0; i < k; ++i) {
    //cout << "found: " << dist_map[i] << " ";
    if(min_dist == -1 || min_dist > dist_map[i])
      min_dist = dist_map[i];
  }
  return min_dist;
}

void testcase() {
  // read Inputs
  cin >> n >> m >> k >> t;

  vector<int> teleportation_network(t);
  for(int i = 0; i < t; ++i) {
    cin >> teleportation_network[i];
  }

  // Make transposed Graph
  weighted_graph G(n);
  WeightMap weights = get(edge_weight, G);
  int source, dest, w;
  for (int i = 0; i < m; ++i) {
    cin >> source >> dest >> w;
    cur_edge = add_edge(dest, source, G).first; weights[cur_edge] = w;
  }

  // Set up Teleportation Network in G
  vector<int> scc_map(n);
  int nscc = strong_components(G,make_iterator_property_map(scc_map.begin(), get(vertex_index, G)));

  vector<vector<int>> linked(nscc, vector<int>());
  for(auto elem : teleportation_network) {
    linked[scc_map[elem]].push_back(elem);
  }

  for(int i = 0; i < nscc; ++i) {
    vertex_desc teleporter = add_vertex(G);
    for(int j = 0; j < linked[i].size(); ++j) {
      //cout << "add edge: " << teleportation_network[i] << " " << teleportation_network[j] << " ";
      cur_edge = add_edge(linked[i][j], teleporter, G).first;
      weights[cur_edge] = linked[i].size() - 1;
      //cout <<  << endl;
      cur_edge = add_edge(teleporter, linked[i][j], G).first;
      weights[cur_edge] = 0;
    }
  }

  // Compute Min Distance
  int min_dist = dijkstra_path(G, n-1, 0);
  if(min_dist < 1000000)
    cout << min_dist << endl;
  else
    cout << "no" << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
