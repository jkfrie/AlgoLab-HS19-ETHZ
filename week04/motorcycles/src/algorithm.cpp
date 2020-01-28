#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>
#include <CGAL/squared_distance_2.h>

#include <iostream> // We will use C++ input/output via streams
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

struct Motorcycle {
 long y0;
 int index;
 R ray;

 Motorcycle(long y, int i, R r) : y0(y), index(i), ray(r) {}
};

// Linearly order motorcycles by y0 decreasing (that's why > is flipped in return statement)
bool operator < (const Motorcycle& m1, const Motorcycle& m2) {
 return (m1.y0 > m2.y0);
}

void testcase() {

 // Read input and create set of motos
 int n;
 cin >> n;
 set<Motorcycle> motos;

 long y0,x1,y1;
 for(int i = 0; i < n; ++i) {
   std::cin >> y0 >> x1 >> y1;
   motos.insert(Motorcycle(y0, i, R(P(0, y0), P(x1, y1))));
 }

 // get y0 of last moto to know when to stop the algorithm
 long endY = (--motos.end())->y0;

 // Check if moto intersects next moto
 auto prev = motos.begin();
 for (auto it = motos.begin(); it != motos.end(); ) {
   //cout << "prev: " << prev->index << ", " << "elem: " << it->index << endl;
   if(it->y0 != motos.begin()->y0 && CGAL::do_intersect(prev->ray, it->ray)) {
     // Be careful pointers get invalidated when erasing element!
     auto tmp = it;
     ++tmp;
     motos.erase(*it);
     it = tmp;
     //cout << "erase: " << it->index << endl;
   }
   else {
     prev = it;
     ++it;
   }

   // print set of motorcycles
   /*
   cout << "motos: ";
   for(auto elem : motos) {
     cout << elem.index << " ";
   }
   cout << endl;
   */
 }

 // Output result
 vector<int> results;
 for (auto elem : motos)
   results.push_back(elem.index);
 sort(results.begin(), results.end());

 for(auto elem : results) {
   cout << elem << " ";
 }
 cout << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
