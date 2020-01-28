#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>
#include <CGAL/squared_distance_2.h>

#include <iostream> // We will use C++ input/output via streams
#include <string>
#include <vector>
#include <limits>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef std::vector<S> VS;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase(int n) {

  // Read input
  VS segments(n);
  long x,y,a,b;
  std::cin >> x >> y >> a >> b;
  P startPoint = P(x,y);
  R ray = R(startPoint, P(a,b));
  S segmentedRay;

  long r,s,t,u;
  for(int i = 0; i < n; ++i) {
    std::cin >> r >> s >> t >> u;
    segments[i] = S(P(r, s), P(t, u));
  }

  // Shuffle the vector of segment in case of adversarial input
  std::random_shuffle(segments.begin(), segments.end());

  // Check if ray intersects any segment.
  bool hasIntersec = false;
  bool curHasIntersec = false;
  K::FT curDist;
  K::FT minDist = -1;
  P firstIntersec;

  boost::optional< boost::variant<K::Point_2, K::Segment_2>> o;

  for (int i = 0; i < n; ++i) {

    if(hasIntersec) {
      curHasIntersec = CGAL::do_intersect(segmentedRay, segments[i]);
      //std::cout << "quicky: " << curHasIntersec << std::endl;
    }
    else {
      curHasIntersec = CGAL::do_intersect(ray, segments[i]);
    }

    if (curHasIntersec) {

      if(hasIntersec) {
        o = CGAL::intersection(segmentedRay, segments[i]);
        //std::cout << "quicky2" << std::endl;
      }
      else {
        o = CGAL::intersection(ray, segments[i]);
      }

      hasIntersec = true;

      // Check if Intersection is a point
      if (const P* op = boost::get<P>(&*o)) {
        curDist = CGAL::squared_distance(startPoint, *op);
        if (minDist <= -1 || curDist < minDist) {
           firstIntersec = *op;
           segmentedRay = S(startPoint, firstIntersec);
           minDist = curDist;
          //std::cout << "foundP:" << floor_to_double(firstIntersec.x()) << " " << floor_to_double(firstIntersec.y()) << std::endl;
        }
      }

      // Check if Intersection is a segment
      else if (const S* os = boost::get<S>(&*o)) {
        curDist = CGAL::squared_distance(startPoint, os->source());
        //std::cout << "curDist: " << curDist << std::endl;
        if (minDist <= -1 || curDist < minDist) {
          minDist = curDist;
          firstIntersec = os->source();
          segmentedRay = S(startPoint, firstIntersec);
          //std::cout << "foundS1:" << floor_to_double(firstIntersec.x()) << " " << floor_to_double(firstIntersec.y()) << std::endl;
        }
        curDist = CGAL::squared_distance(startPoint, os->target());
        //std::cout << "curDist: " << curDist << std::endl;
        if (minDist <= -1 || curDist < minDist) {
          minDist = curDist;
          firstIntersec = os->target();
          segmentedRay = S(startPoint, firstIntersec);
          //std::cout << "foundS2:" << floor_to_double(firstIntersec.x()) << " " << floor_to_double(firstIntersec.y()) << std::endl;
        }
      }
    }
  }

  // output result
  if (hasIntersec) {
    std::cout << std::fixed << std::setprecision(0) << floor_to_double(firstIntersec.x()) << " " << floor_to_double(firstIntersec.y()) << std::endl;
  }
  else {
    std::cout << "no" << std::endl;
  }
}

int main() {
  int n; std::cin >> n;
  while (n) {
    testcase(n);
    std::cin >> n;
  }
}
