#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;

using namespace std;

#define REP(i, n) for (int i = 0; i < n; ++i)

void testcase(int n) {
  cout << setprecision(0);

  // read current resteraunts
  std::vector<K::Point_2> cur_bistros;
  cur_bistros.reserve(n);
  for (std::size_t i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    cur_bistros.push_back(K::Point_2(x, y));
  }

  // construct triangulation
  Triangulation t;
  t.insert(cur_bistros.begin(), cur_bistros.end());

  // read new bistro locations and compute distance to closest bistro
  int m;
  cin >> m;
  K::FT dist;
  for (std::size_t i = 0; i < m; ++i) {
    int x, y;
    std::cin >> x >> y;
    K::Point_2 new_loc(x, y);
    dist = CGAL::squared_distance(new_loc, t.nearest_vertex(new_loc)->point());
    cout << fixed << dist << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n;
  cin >> n;
  while (n) {
    testcase(n);
    cin >> n;
  }
}
