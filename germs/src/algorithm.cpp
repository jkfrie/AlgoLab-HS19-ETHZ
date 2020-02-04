#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Delaunay;
typedef Delaunay::Edge_iterator Edge_iterator;

#define REP(i, n) for(int i = 0; i < n; ++i)

double get_time(K::FT squared_dist) {
	double x = sqrt(CGAL::to_double(squared_dist));
	return ceil(sqrt(x/2.0 - 0.5));
}

void testcase(int n) {
  int l, d, r, u;
  cin >> l >> d >> r >> u;

  // read bacteria locations
  typedef std::pair<K::Point_2, Index> IPoint;
  std::vector<IPoint> points;
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.push_back(make_pair(K::Point_2(x, y), i));
  }

  // create vector that stores for every bacterium closest dist to a border
  vector<K::FT> dists;
  REP(i, n) {
	long x = points[i].first.x();
	long y = points[i].first.y();
	K::FT dist = x - l;
	//cout << dist << " ";
	dist = min(dist, K::FT(r - x));
	//cout << dist << " ";
	dist = min(dist, K::FT(u - y));
	//cout << dist << " ";
	dist = min(dist, K::FT(y - d));
	//cout << dist << " " << endl;
	dist *= dist * 4;
	dists.push_back(dist);
  }



  // Construct Delaunay Triangulation
  Delaunay t;
  t.insert(points.begin(), points.end());

  // iterate over all edges and store it for each vertex if length smallest
  for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    K::FT dist = t.segment(e).squared_length();
	int u = e->first->vertex((e->second + 1) % 3)->info();
	int v = e->first->vertex((e->second + 2) % 3)->info();
    dists[u] = min(dists[u], dist);
	dists[v] = min(dists[v], dist);
  }

  sort(dists.begin(), dists.end());

  cout << get_time(dists[0]) << " " << get_time(dists[n/2]) << " " << get_time(dists[n - 1]) << endl;
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  while(t) {
	 testcase(t);
	 cin >> t;
  }
}
