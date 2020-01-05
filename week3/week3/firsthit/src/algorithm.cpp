#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

#define REP(i, n) for(int i = 0; i < n; ++i)

double floor_to_double(const K::FT& x){
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void shorten_segment(S& s, const std::result_of<K::Intersect_2(S,S)>::type& o) {
  if (const P* op = boost::get<P>(&*o))
    s = S(s.source(), *op);
  else if (const S* os = boost::get<S>(&*o)) {
    if(CGAL::squared_distance(os->source(), s.source()) < CGAL::squared_distance(os->target(), s.source()))
      s = S(s.source(), os->source());
    else
      s = S(s.source(), os->target());
  }
}

void testcase(int n) {
  long x, y, a, b; cin >> x >> y >> a >> b;
  R ray = R(P(x,y), P(a,b));
  S rc = S(P(x,y), P(a,b));

  vector<S> segments(n);
  REP(i, n) {
    long r, s, t, u; cin >> r >> s >> t >> u;
    segments[i] = S(P(r, s), P(t, u));
  }

  // shuffle segments to counteract adversarial Input
  random_shuffle(segments.begin(), segments.end());

  // find any hit
  int first_hit = -1;
  REP(i, n) {
    if (CGAL::do_intersect(segments[i], ray)) {
       first_hit = i;
	     auto o = CGAL::intersection(segments[i], ray);
       shorten_segment(rc, o);
       break;
    }
  }

  // early abort if no intersection
  if(first_hit < 0) {
    cout << "no" << endl;
    return;
  }

  // loop over all segments but check for intersections on clipped Ray
  int i = first_hit;
  while(++i < n) {
    if (CGAL::do_intersect(segments[i], rc)) {
	     auto o = CGAL::intersection(segments[i], rc);
       shorten_segment(rc, o);
    }
  }

  cout << setprecision(0) << fixed << floor_to_double(rc.target().x()) << " " << floor_to_double(rc.target().y()) << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    while(n) {
      testcase(n);
      cin >> n;
    }
}
