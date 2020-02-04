#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;

#define REP(i, n) for (int i = 0; i < n; ++i)

void testcase() {
  int m, n;
  cin >> m >> n;
  vector<pair<K::Point_2, double>> persons;
  persons.reserve(m);
  REP(i, m) {
	  K::Point_2 x; double r; cin >> x >> r;
	  persons.push_back(make_pair(x, r));
  }

  double h; cin >> h;

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

  // iterate over all persons and check which one does not get hit by lamp
  vector<int> result;
  
  REP(i, m) {
	  auto nearest = t.nearest_vertex(persons[i].first)->point();
	  double dist = CGAL::squared_distance(nearest, persons[i].first);
	  if(dist >= (h+persons[i].second) * (h+persons[i].second)) {
		 result.push_back(i); 
	  }
  }

  for(auto elem : result) {
	  cout << elem << " ";
  }
  cout << "\n";

  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) testcase();
}
