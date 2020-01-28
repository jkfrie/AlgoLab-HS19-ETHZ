#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// type definitions
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K>  Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;
typedef std::vector<P> VP;

VP homes;

double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void testcase(int n) {

  // Read input
  homes = VP();
  long x,y;
  for(int i = 0; i < n; ++i) {
    std::cin >> x >> y;
    homes.push_back(P(x, y));
  }

  // Compute Min Circle for all homes
  Min_circle mc(homes.begin(), homes.end(), true);
  Traits::Circle c = mc.circle();

  // Loop over all supporting point and compute MC without this home
  K::FT curMin = -1;
  K::FT curRadius;
  P tmp;
  int curIndex;

  for(int i = 0; i < n; ++i) {
    for (int j = 0; j < mc.number_of_support_points(); j++) {
      //std::cout << "i: " << homes[i] << " SP: " << mc.support_point(j) << std::endl;
      if(homes[i] == mc.support_point(j)) {
        tmp = homes[i];
        homes[i] = homes[(i+1)%n];

        /*
        std::cout << "homes: ";
        for(auto elem : homes) {
          std::cout << elem << ", ";
        }
        std::cout << std::endl;
        */

        Min_circle mc2(homes.begin(), homes.end(), true);
        Traits::Circle c2 = mc2.circle();
        curRadius = c2.squared_radius();
        //std::cout << "curRadius: " << curRadius << std::endl;
        if(curMin == -1 || curRadius < curMin)
          curMin = curRadius;
        homes[i] = tmp;
      }
    }
  }

  K::FT radius = CGAL::sqrt(curMin);

  // Output result
  std::cout << std::setprecision(0) << std::fixed << ceil_to_double(radius) << std::endl;
}

int main() {
  int n; std::cin >> n;
  while (n) {
    testcase(n);
    std::cin >> n;
  }
}
