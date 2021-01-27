#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <algorithm>
#include <boost/pending/disjoint_sets.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Delaunay;

// As edges are not explicitly represented in the triangulation, we extract them
// from the triangulation to be able to sort and process them. We store the
// indices of the two endpoints, first the smaller, second the larger, and third
// the squared length of the edge. The i-th entry, for i=0,... of a tuple t can
// be accessed using std::get<i>(t).
typedef std::tuple<Index, Index, K::FT> Edge;
typedef std::vector<Edge> EdgeV;

#define REP(i, n) for (int i = 0; i < n; ++i)

std::ostream& operator<<(std::ostream& o, const Edge& e) {
  return o << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e);
}

bool colorable(Delaunay &t, K::FT r_squared) {

	for()
}

void testcase() {
  Index n, m;
  K::FT r;
  std::cin >> n >> m >> r;
  K::FT r_squared = r * r;

  // read points: first, we read all points and store them into a vector,
  // together with their indices
  typedef std::pair<K::Point_2, Index> IPoint;
  std::vector<IPoint> points;
  points.reserve(n);
  for (Index i = 0; i < n; ++i) {
    int x, y;
    std::cin >> x >> y;
    points.emplace_back(K::Point_2(x, y), i);
  }

  vector<pair<K::Point_2, K::Point_2>> clues;
  clues.reserve(n);
  REP(i, m) {
    K::Point_2 a, b;
    cin >> a >> b;
    clues.push_back(make_pair(a, b));
  }

  // then we build the Delaunay triangulation in one shot, so as to leave the
  // choice of an efficient insertion order to the triangulation structure. By
  // giving the points paired with the indices, these indices are used to
  // initialize the vertex info accordingly.
  // This step takes O(n log n) time (for constructing the triangulation).
  Delaunay t;
  t.insert(points.begin(), points.end());

  // extract edges and sort by (squared) length
  // This step takes O(n log n) time (for the sorting).
  EdgeV edges;
  edges.reserve(3 * n);  // there can be no more in a planar graph
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    Index i1 = e->first->vertex((e->second + 1) % 3)->info();
    Index i2 = e->first->vertex((e->second + 2) % 3)->info();
    // ensure smaller index comes first
    if (i1 > i2) std::swap(i1, i2);
    edges.emplace_back(i1, i2, t.segment(e).squared_length());
  }
  std::sort(edges.begin(), edges.end(),
            [](const Edge& e1, const Edge& e2) -> bool {
              return std::get<2>(e1) < std::get<2>(e2);
            });

  // Compute EMST using Kruskal's algorithm. This step takes O(n alpha(n)) time
  // in theory; for all practical purposes alpha(n) is constant, so linear time.

  // setup and initialize union-find data structure
  boost::disjoint_sets_with_storage<> uf(n);
  Index n_components = n;
  // ... and process edges in order of increasing length
  for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
    if (get<2>(*e) <= r_squared) {
      // determine components of endpoints
      Index c1 = uf.find_set(std::get<0>(*e));
      Index c2 = uf.find_set(std::get<1>(*e));
      if (c1 != c2) {
        // this edge connects two different components => part of the emst
        uf.link(c1, c2);
        //std::cout << *e << "\n";
        if (--n_components == 1) break;
      }
    }
	else break;
  }

  // check which clues can be transmitted assuming there exists a network
  // without interference.
  for(auto elem : clues) {
	  auto a_nearest = t.nearest_vertex(elem.first);
	  auto b_nearest = t.nearest_vertex(elem.second);
	  K::FT dist1 = CGAL::squared_distance(elem.first, a_nearest->point());
	  K::FT dist2 = CGAL::squared_distance(elem.second, b_nearest->point());
	  K::FT max_dist = max(dist1, dist2);
	  Index c1 = uf.find_set(a_nearest->info());
      Index c2 = uf.find_set(b_nearest->info());

	  if((max_dist <= r_squared && c1==c2) || CGAL::squared_distance(elem.first, elem.second) <= r_squared) {
		  cout << "y";
	  }
	  else cout << "n";
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
