#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

typedef  CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;
typedef  K::Point_2                      P;

double ceil_to_double(const K::FT& x){
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void testcase(int n) {
  vector<P> homes(n);
  long x,y;
  for(int i = 0; i < n; ++i) {
    std::cin >> x >> y;
    homes[i] = P(x, y);
  }

  Min_circle mc(homes.begin(), homes.end(), true);
  Traits::Circle c = mc.circle();

  // iterate over the support points and make a min circle without it
  K::FT min_radius = -1;
  REP(i, n) {
    REP(j, mc.number_of_support_points()) {
      if(homes[i] == mc.support_point(j)) {
        P tmp = homes[i];
        homes[i] = homes[(i + 1) % n];

        Min_circle mc2(homes.begin(), homes.end(), true);
        Traits::Circle c2 = mc2.circle();

        if(min_radius == -1 || min_radius > c2.squared_radius()) {
          min_radius = c2.squared_radius();
        }

        homes[i] = tmp;
      }
    }
  }
  min_radius = CGAL::sqrt(min_radius);

  // Output result
  std::cout << std::setprecision(0) << std::fixed << ceil_to_double(min_radius) << std::endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    while(n) {
      testcase(n);
      cin >> n;
    }
}
