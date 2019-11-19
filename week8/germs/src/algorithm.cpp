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
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Edge_circulator Edge_circulator;

#define REP(i, n) for (int i = 0; i < (n); ++i)

using namespace std;

int to_time(double d) {
	//cout << d << " ";
	d = sqrt(d / 4);
	if(d - 0.5 < 0)
		return 0;
	else
		return ceil(sqrt(d - 0.5));
}

void testcase(int n) {

  // Read input
  int l, b, r, t; cin >> l >> b >> r >> t;

  int x, y;
  vector<K::Point_2> pts(n);
  REP(i, n) {
    cin >> x >> y;
    pts[i] = K::Point_2(x, y);
  }

  // Set up Triangulation
  Triangulation tr;
  tr.insert(pts.begin(), pts.end());

  // Loop over query points and find closest distance
  cout << fixed << setprecision(0);
  vector<long> distances;
  for (Vertex_iterator v = tr.finite_vertices_begin(); v != tr.finite_vertices_end(); ++v) {
    Edge_circulator c = tr.incident_edges(v);
    long min_dist = numeric_limits<int>::max();
    min_dist = min(v->point().x() - l, r - v->point().x());
    //cout << min_dist << " ";
    min_dist = min(min_dist, (long) min(t - v->point().y(), v->point().y() - b));
    //cout << min_dist << " ";
    min_dist *= min_dist * 4; // to make it same as squared distances we use after and b.c. border doesnt grow.
    //cout << min_dist << " ";
    if(c != 0) {
      do {
				if(!tr.is_infinite(c)) {
					min_dist = min((long) CGAL::to_double(tr.segment(c).squared_length()), min_dist);
					//cout << min_dist << " ";
				}
      } while (++c != tr.incident_edges(v));
    }
    distances.push_back(min_dist);
    //cout << endl;
  }

  // Sort distances
  sort(distances.begin(), distances.end());

	/*
  for(auto elem : distances) {
    cout << elem << " ";
  }
  cout << endl;
	*/

  cout << to_time(distances[0]) << " " << to_time(distances[n/2]) << " " << to_time(distances[n - 1]) << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    while(n) {
      testcase(n);
      cin >> n;
    }
}
