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
  K::FT radius = CGAL::sqrt(c.squared_radius());

  // Output result
  std::cout << std::setprecision(0) << std::fixed << ceil_to_double(radius) << std::endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    while(n) {
      testcase(n);
      cin >> n;
    }
}
