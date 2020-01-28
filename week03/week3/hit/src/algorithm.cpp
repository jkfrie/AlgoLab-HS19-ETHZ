#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase(int n) {
  long x, y, a, b; cin >> x >> y >> a >> b;
  R ray = R(P(x,y), P(a,b));

  string result = "no";
  vector<S> segments(n);
  REP(i, n) {
    long r, s, t, u; cin >> r >> s >> t >> u;
    segments[i] = S(P(r, s), P(t, u));
    if(CGAL::do_intersect(segments[i], ray)) {
      result = "yes";
    }
  }
  cout << result << endl;
}

int main() {
  int n; std::cin >> n;
  while(n) {
    testcase(n);
    std::cin >> n;
  }
}
