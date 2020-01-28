#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

using namespace std;
using namespace boost;

typedef CGAL::Exact_predicates_inexact_constructions_kernel    K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>    Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef Triangulation::Edge_iterator                           Edge_iterator;
typedef boost::disjoint_sets_with_storage<>                    UF;

#define REP(i, n) for(int i = 0; i < n; ++i)

int n, m;
long p;

// Custom Edge type to make things easier
struct Edge {
  int start, end;
  K::FT sq_length;

  Edge(int s, int e, K::FT sql) : start(s), end(e), sq_length(sql) {}
};

bool operator < (const Edge& e1, const Edge& e2) {
  return (e1.sq_length < e2.sq_length);
}

K::FT get_max_dist(const vector<Edge> &edges, const vector<pair<K::Point_2, K::Point_2>> &missions,
  const vector<bool> &possible, const Triangulation &t) {

  // Create UnionFind datastructure tu represent connected jammers
  UF uf(n);

  // Loop over missions and add edges until all required missions are possible
  K::FT max_dist = 0;
  K::FT dist;
  auto it = edges.begin();
  REP(i, m) {
    // Do we need mission i to be possible?
    if(possible[i]) {
      auto nearest_s = t.nearest_vertex(missions[i].first);
      auto nearest_t = t.nearest_vertex(missions[i].second);
      dist = CGAL::squared_distance(nearest_s->point(), missions[i].first) * 4;
      dist = max(dist, CGAL::squared_distance(nearest_t->point(), missions[i].second) * 4);
      int c1 = uf.find_set(nearest_s->info());
      int c2 = uf.find_set(nearest_t->info());

      // Add edges until start and end of mission are in same component
      while(it != edges.end() && c1 != c2) {
        dist = max(dist, it->sq_length);
        uf.union_set(it->start, it->end);
        c1 = uf.find_set(nearest_s->info());
        c2 = uf.find_set(nearest_t->info());
        ++it;
      }

      // Update max distance
      max_dist = max(max_dist, dist);
    }
  }
  return max_dist;
}

void testcase() {
  // Read input variables
  n, m, p; cin >> n >> m >> p;

  // Read in jammers
  vector<pair<K::Point_2, int>> jammers;
  REP(i, n) {
    K::Point_2 pt;
    cin >> pt;
    jammers.push_back(make_pair(pt, i));
  }

  // Read in missions
  vector<pair<K::Point_2, K::Point_2>> missions;
  REP(i, m) {
    K::Point_2 src, target;
    cin >> src >> target;
    missions.push_back(make_pair(src, target));
  }

  // Create Triangulation of jammers (will contain min euclidean spanning tree)
  Triangulation t;
  t.insert(jammers.begin(), jammers.end());

  // Create UnionFind datastructure tu represent connected jammers
  UF uf(n);

  // Loop over all edges and convert to custom edges.
  vector<Edge> edges;
  edges.reserve(3*n); // there can be no more in a planar graph!
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int v1 = e->first->vertex((e->second + 1) % 3)->info();
    int v2 = e->first->vertex((e->second + 2) % 3)->info();
    edges.push_back(Edge(v1, v2, t.segment(e).squared_length()));
  }

  // Sort the edges according to increasing edge length
  sort(edges.begin(), edges.end());

  // Compute connected jammers with Union find data structure
  for(auto e : edges) {
    if(e.sq_length <= p) uf.union_set(e.start, e.end);
  }

  // Loop over missions and test if they are connected
  vector<bool> possible(m, false);
  REP(i, m) {
    auto nearest_s = t.nearest_vertex(missions[i].first);
    auto nearest_t = t.nearest_vertex(missions[i].second);
    K::FT dist = CGAL::squared_distance(nearest_s->point(), missions[i].first) * 4;
    dist = max(dist, CGAL::squared_distance(nearest_t->point(), missions[i].second) * 4);

    if(dist <= p) {
      int c1 = uf.find_set(nearest_s->info());
      int c2 = uf.find_set(nearest_t->info());

      if(c1 == c2) possible[i] = true;
    }
  }

  // output result
  for(auto elem : possible) {
    if (elem) cout << "y";
    else cout << "n";
  }
  cout << endl;

  cout << setprecision(0) << fixed << get_max_dist(edges, missions, vector<bool>(m, true), t) << endl;
  cout << setprecision(0) << fixed << get_max_dist(edges, missions, possible, t) << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
      testcase();
    }
}
