#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;

double ceil_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a + 1 <= x) a += 1;
  return a;
}

void testcase(int n) {
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
  // output all edges
  K::FT min_dist = -1;
  for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end();
       ++e) {
    K::FT cur_dist = t.segment(e).squared_length();
    if (min_dist == -1 || min_dist > cur_dist) min_dist = cur_dist;
  }
  cout << ceil(sqrt(CGAL::to_double(min_dist)) * 50) << "\n";
  return;
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
