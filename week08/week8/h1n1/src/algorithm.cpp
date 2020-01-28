#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Face_iterator Face_iterator;
typedef Triangulation::Edge_iterator Edge_iterator;

typedef boost::adjacency_list<boost::setS, boost::vecS, boost::undirectedS,
                              boost::no_property,
                              boost::property<boost::edge_weight_t, long> >
    weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type
    weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

#define REP(i, n) for (int i = 0; i < n; ++i)

long min_dist(std::vector<vertex_desc> &primpredmap, int i, weight_map &weights,
              weighted_graph &G, vector<long> &min_d) {
  if (min_d[i] == -1) {
    edge_desc e = boost::edge(i, primpredmap[i], G).first;
	//cout << e.m_source << " " << e.m_target << endl;
    min_d[i] = min(LONG_MAX - weights[e],
                   min_dist(primpredmap, primpredmap[i], weights, G, min_d));
  }
  return min_d[i];
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

  // store face index in face info
  int cur_index = 1;  // 0 is reserved for infinite faces
  for (Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end();
       ++f) {
    f->info() = cur_index;
    cur_index++;
  }
  int nr_faces = cur_index;

  // Find Prim MST starting at infinite faces,
  // where edgeweight = MAX - squared edgelength / 4 between the faces
  weighted_graph G(nr_faces);
  weight_map weights = boost::get(boost::edge_weight, G);
  edge_desc e;

  for (Face_iterator f = t.finite_faces_begin(); f != t.finite_faces_end();
       ++f) {
    int index_1 = f->info();
    REP(i, 3) {
      int index_2;
      if (t.is_infinite(f->neighbor(i)))
        index_2 = 0;
	  else 
        index_2 = f->neighbor(i)->info();
      auto v1 = f->vertex((i + 1) % 3);
      auto v2 = f->vertex((i + 2) % 3);
      long dist =
          CGAL::to_double(CGAL::squared_distance(v1->point(), v2->point()));
      e = boost::add_edge(index_1, index_2, G).first;
	  //cout << "add edge: " << index_1 << " " << index_2 << " " << dist << endl; 
      weights[e] = LONG_MAX - dist / 4;
    }
  }

  std::vector<vertex_desc> primpredmap(nr_faces);
  vertex_desc start = 0;
  boost::prim_minimum_spanning_tree(
      G,
      boost::make_iterator_property_map(primpredmap.begin(),
                                        boost::get(boost::vertex_index, G)),
      boost::root_vertex(start));

  // find vector min_dist with minimal d to get free
  vector<long> min_d(nr_faces, -1);
  min_d[0] = LONG_MAX;
  //cout << "min_dist: ";
  for(int i = 1; i < nr_faces; ++i) { min_dist(primpredmap, i, weights, G, min_d); }

  // Check for each person if it is possible to get away
  int m; cin >> m;
  REP(i, m) {
	  int x, y; long d; cin >> x >> y >> d;
	  K::Point_2 person(x,y);

	  // check if person already closer than d to an infected person
	  auto closest = t.nearest_vertex(person);
	  if(CGAL::squared_distance(person, closest->point()) < d) {
		  cout << "n"; continue;
	  }
	  // else check if min_d on route to freedom is smaller than d
	  else {
		  auto cur_face = t.locate(person);
		  if(t.is_infinite(cur_face)) cout << "y";
		  else if(min_d[cur_face->info()] < d) cout << "n";
		  else cout << "y";
	  }
  }

  cout << endl;
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
