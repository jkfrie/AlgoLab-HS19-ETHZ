#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <iostream> // We will use C++ input/output via streams
#include <string>
#include <set>
#include <limits>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef std::vector<S> VS;

void testcase(int n) {

  VS segments(n);
  long x,y,a,b;
  std::cin >> x >> y >> a >> b;
  R ray = R(P(x,y), P(a,b));

  long r,s,t,u;
  for(int i = 0; i < n; ++i) {
    std::cin >> r >> s >> t >> u;
    segments[i] = S(P(r, s), P(t, u));
  }

  // Check if ray intersects any segment.
  std::string result = "no";
  for(int i = 0; i < n; ++i) {
    if(CGAL::do_intersect(ray, segments[i])){
      result = "yes";
      break;
    }
  }
  std::cout << result << std::endl;
}

int main() {
  int n; std::cin >> n;
  while (n) {
    testcase(n);
    std::cin >> n;
  }
}
