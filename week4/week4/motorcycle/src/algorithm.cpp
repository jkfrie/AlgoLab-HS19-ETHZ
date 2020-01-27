#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;
#define REP(i, n) for(int i = 0; i < n; ++i)

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;

struct Bike {
  long y0;
  int index;
  K::FT slope;
  R ray;

  Bike(long y, int i, K::FT s, R r) : y0(y), index(i), slope(s), ray(r) {}
};

bool operator < (const Bike& b1, const Bike& b2) {
return (b1.y0 < b2.y0);
}

void testcase() {
  int n; cin >> n;
  vector<Bike> bikes;
  REP(i, n) {
    long y, x1, y1; cin >> y >> x1 >> y1;
    R ray = R(P(0,y), P(x1,y1));
    K::FT slope = ray.direction().dy() / ray.direction().dx();
    Bike b(y, i, slope, ray);
    bikes.push_back(b);
  }

  // sort bikes according to increasing y0
  sort(bikes.begin(), bikes.end());

  // go through all bikes starting with max y0 and save current riders on stack
  // if they don't intersect with previous. If they intersect either delete previous
  // or current. if we delete previous might have to also delete new previous a.s.o.
  vector<Bike> current_riders;
  current_riders.push_back(bikes[0]);

  for(int i = 1; i < n; ++i) {
    bool cur_rides = true;
    while(!current_riders.empty() && cur_rides) {
      Bike prev_bike = current_riders.back();
      if (CGAL::do_intersect(bikes[i].ray, prev_bike.ray)) {
        // Case: keep cur_bike
        if(prev_bike.slope + bikes[i].slope > 0) {
          //cout << "keep prev bike! " << endl;
          current_riders.pop_back();
        }
        // Case: keep bike[i]
        else {
          cur_rides = false;
          //cout << "keep cur bike " << i << " !" << endl;
        }
      }
      // Case both bikes continue
      else {
        //cout << "both bikes continue!" << endl;
        break;
      }
    }

    if(cur_rides) current_riders.push_back(bikes[i]);
    //if(cur_rides) cout << "push_back bike " << i << endl;
  }

  vector<int> result_indexes;
  for(auto elem : current_riders) {
    result_indexes.push_back(elem.index);
  }
  sort(result_indexes.begin(), result_indexes.end());

  for(auto elem : result_indexes) {
    cout << elem << " ";
  }
  cout << "\n";

}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
