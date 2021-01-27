#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {

  // Read input
  int m, n; cin >> m >> n;

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

  // Make a Triangulation on all lamps
  Triangulation t;
  t.insert(lamps.begin(), lamps.end());

  // For each person check if nearest lamp hits him. If not add person to winners
  int max_rounds = 0;
  vector<int> rounds(m, -1);
  REP(i, m) {

    auto nearest = t.nearest_vertex(persons[i].first);
    K::FT dist = CGAL::squared_distance(persons[i].first, nearest->point());
    // Check if no light hits person, then he is a winner
    if(dist - pow((long long) persons[i].second + (long long) h, 2) >= 0) {
        rounds[i] = INT_MAX;
        //cout << "person: " << i << " No lamp!!" << endl;
        max_rounds = INT_MAX;
    }
  }

  // If all persons are hit by a light find winners by checking for each person
  // all lights
  if(max_rounds != INT_MAX) {
    REP(i, m) {
      if(max_rounds != INT_MAX) {
        REP(j, n) {
          K::FT dist = CGAL::squared_distance(persons[i].first, lamps[j]);
          //cout << "person: " << i << " lamp:" << j << " dist: " << dist << " " << persons[i].second << " " << h << endl;
          // Check if person is hit
          if(dist - pow((long long) persons[i].second + (long long) h, 2) < 0) {
            rounds[i] = j;
            max_rounds = max(max_rounds, j);
            //cout << "person: " << i << " take lamp:" << j << endl;
            break;
          }
        }
      }
    }
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
