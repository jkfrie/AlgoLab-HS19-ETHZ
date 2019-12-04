#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {

  // Read input
  int m; cin >> m;
  long n; cin >> n; 

  vector<pair<K::Point_2, int>> persons;
  REP(i, m) {
    int x, y, r; cin >> x >> y >> r;
    persons.push_back(make_pair(K::Point_2(x, y), r));
  }

  int h; cin >> h;

  vector<K::Point_2> lamps;
  REP(i, n) {
    int x, y;
    cin >> x >> y;
    lamps.push_back(K::Point_2(x, y));
  }

  // For each person go through all lamps until it is hit by the light and mark
  // which round the person got hit.
  int max_rounds = 0;
  vector<int> rounds(m, INT_MAX);
  REP(i, m) {
    // Loop over all lamps
    REP(j, n) {
      K::FT dist = CGAL::squared_distance(persons[i].first, lamps[j]);
      //cout << "person: " << i << " lamp:" << j << " dist: " << dist << " " << persons[i].second << " " << h << endl;
      // Check if person is hit
      if(dist - pow((long long) persons[i].second + (long long) h, 2) < 0) {
        rounds[i] = j;
        max_rounds = max(max_rounds, j);
        //cout << "person: " << i << " take lamp:" << j << endl;
        continue;
      }
    }
    // If no light hit person, then mark max_rounds as INT_MAX
    if(rounds[i] == INT_MAX) max_rounds = INT_MAX;
  }

  // Go through rounds again and outpu all that contain max_rounds
  REP(i, m) {
    if (rounds[i] == max_rounds) cout << i << " ";
  }
  cout << endl;
}


int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
