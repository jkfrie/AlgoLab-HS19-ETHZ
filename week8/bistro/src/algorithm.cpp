#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_edges_iterator  Edge_iterator;

#define REP(i, n) for (int i = 0; i < (n); ++i)

using namespace std;

double ceil_to_double(const K::FT& x) {
	double a = std::ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a-1 >= x) a -= 1;
	return a;
}

void testcase(int n) {

  // Read input
  int x, y;
  vector<K::Point_2> pts(n);
  REP(i, n) {
    cin >> x >> y;
    pts[i] = K::Point_2(x, y);
  }

  // Set up Triangulation
  Triangulation t;
  t.insert(pts.begin(), pts.end());

  // Loop over query points
  int m; cin >> m;
  cout << fixed << setprecision(0);
  REP(i, m) {
    cin >> x >> y;
    K::Point_2 query = K::Point_2(x, y);
    K::Point_2 nearest = t.nearest_vertex(query)->point();
    cout << (long long int) CGAL::squared_distance(nearest, query) << endl;
  }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    while(n) {
      testcase(n);
      cin >> n;
    }
}
