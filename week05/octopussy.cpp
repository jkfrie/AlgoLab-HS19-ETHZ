#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
  int n; cin >> n;
  vector<int> times(n);
  REP(i, n) cin >> times[i];

  // Adjust times of balls on ground
  REP(i, (n-3)/2 + 1) {
    times[2*i + 1] = min(times[2*i + 1], times[i] - 1);
    times[2*i + 2] = min(times[2*i + 2], times[i] - 1);
  }

  // Greedy Algorithm: earliest deadline first
  sort(times.begin(), times.end());
  int cur_time = 0;
  string result = "yes";
  REP(i, n) {
    cur_time++;
    //cout << "cur_time: " << cur_time << " expl: " << times[i] << endl;
    if(times[i] < cur_time) {
      result = "no";
      break;
    }
  }

  cout << result << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
