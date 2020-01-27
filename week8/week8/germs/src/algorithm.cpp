#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Vertex_iterator Vertex_iterator;

using namespace std;

#define REP(i, n) for (int i = 0; i < n; ++i)

int dist_to_time(K::FT dist) {
  double x = CGAL::to_double(dist);
  return ceil((sqrt(sqrt(x) / 2 - 0.5)));
}

void testcase(int n) {
  // read dish boundaries
  int l, d, r, u;
  cin >> l >> d >> r >> u;

  // read points
  std::vector<K::Point_2> pts;
  pts.reserve(n);
  for (std::size_t i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    pts.push_back(K::Point_2(x, y));
  }

  // construct triangulation
  Triangulation t;
  t.insert(pts.begin(), pts.end());

  // iterate over vertices and find closest other cell or dish boundary
  vector<K::FT> distances;
  for (Vertex_iterator v = t.finite_vertices_begin();
       v != t.finite_vertices_end(); ++v) {
    //std::cout << v->point() << "\n";

    // find min distance to a border
    int x = v->point().x();
    x = x;
    int y = v->point().y();
    y = y;
    K::FT min_dist = K::FT(min(x - l, r - x));
    //cout << "min_dist1: " << min_dist << endl;
    min_dist = min(min_dist, K::FT(min(y - d, u - y)));
    //cout << "min_dist2: " << min_dist << endl;
    min_dist *= min_dist * 4;

    // find all infinite edges incident to v
    Triangulation::Edge_circulator c = t.incident_edges(v);
    if (c != 0) {
      do {
        // cout << t.segment(c) << endl;

        if (!t.is_infinite(c)) {
          // cout << t.segment(c) << endl;
          K::FT cur_dist = t.segment(c).squared_length();
          //cout << "cur_dist: " << cur_dist << endl;

          min_dist = min(min_dist, cur_dist);
          //cout << "min_distx: " << min_dist << endl;
        }
      } while (++c != t.incident_edges(v));
    }

    // Add min_dist to distances
    distances.push_back(min_dist);
  }

  sort(distances.begin(), distances.end());

  cout << dist_to_time(distances[0]) << " " << dist_to_time(distances[n / 2])
       << " " << dist_to_time(distances[n - 1]) << "\n";
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t n;
  cin >> n;
  while (n) {
    testcase(n);
    cin >> n;
  }
}
