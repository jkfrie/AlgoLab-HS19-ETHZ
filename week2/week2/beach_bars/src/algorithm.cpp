#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <cmath>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
  int n; cin >> n;

  vector<int> parasols(n);
  REP(i, n) {cin >> parasols[i];}

  // sort parasols
  sort(parasols.begin(), parasols.end());

  // Start sliding window algorithm
  int r = 0;
  int max_sum = 0;
  int min_dist = numeric_limits<int>::max();
  vector<pair<int,int>> best_locations;
  vector<int> sol_positions;

  REP(l, n) {

    // adjust r to have dist(l,r) maximal 200
    while(r + 1 < n && parasols[r+1] - parasols[l] <= 200) {
      r++;
    }

    // Count nr of parasols in range l,r
    int cur_sum = r - l + 1;
    int dist = parasols[r] - parasols[l];
    int effective_dist = ceil((double) dist / 2);
    int pos = (int) dist / 2 + parasols[l];

    // case: found better location
    if(cur_sum > max_sum || (cur_sum >= max_sum && effective_dist < min_dist)) {
      max_sum = cur_sum;
      min_dist = effective_dist;
      best_locations = vector<pair<int, int>>();
      sol_positions = vector<int>();
      //cout << "update maxsum/mindist: " << max_sum <<  min_dist << endl;
    }

    // case: found equal good location
    if(cur_sum == max_sum && min_dist == effective_dist) {
      if(dist % 2 == 0) {
        sol_positions.push_back(pos);
        //cout << "update sol_pos: " << pos << endl;
        //cout << "l/r: " << l << " " << r << endl;
        //cout << parasols[l] << " " << parasols[r] << endl;
        //cout << "pos: " << pos << endl;
      }
      else {
        sol_positions.push_back(pos);
        sol_positions.push_back(pos + 1);
        //cout << "update sol_pos: " << pos << " " << pos+1 << endl;
        //cout << "l/r: " << l << " " << r << endl;
        //cout << parasols[l] << " " << parasols[r] << endl;
        //cout << "pos: " << pos << endl;
      }
      best_locations.push_back(make_pair(max(pos - parasols[l], parasols[r] - pos), pos));
    }
  }

  // sort solutions
  sort(sol_positions.begin(), sol_positions.end());

  // output result
  cout << max_sum << " " << min_dist << endl;

  for(auto elem : sol_positions) {
    cout << elem << " ";
  }
  cout << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >>t;
    while(t--) testcase();
}
