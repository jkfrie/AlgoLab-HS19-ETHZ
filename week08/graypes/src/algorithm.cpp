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

  // Find shortest edge in Triangulation
  K::FT min_l = -1;
  for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    K::FT l = t.segment(e).squared_length();
    if(min_l == -1 || min_l > l) {
      min_l = l;
    }
  }

  cout << ceil(50 * sqrt(ceil_to_double(min_l))) << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    while(n) {
      testcase(n);
      cin >> n;
    }
}
