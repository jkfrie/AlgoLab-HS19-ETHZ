#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <utility>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
  int n; cin >> n;
  vector<pair<int, int>> boats(n);
  REP(i, n) {
    int l, p; cin >> l >> p;
    boats[i] = make_pair(p, l);
  }

  sort(boats.begin(), boats.end());

  // Start Greedy algorithm
  int min_r = -boats[0].second;
  int prev_r = boats[0].first + 1;
  int sum = 0;
  REP(i, n) {
    //cout << "min_r: " << min_r << " prev_r: " << prev_r << " sum: " << sum << endl;
    //cout << "ring: " << boats[i].first << " length: " << boats[i].second << endl;

    // take previous?
    if(prev_r <= boats[i].first) {
      //cout << "taken" << endl;
      sum++;
      min_r = prev_r;
      prev_r = max(prev_r, boats[i].first - boats[i].second) + boats[i].second;
    }
    // else if current better than prev best delete prev best
    else if(max(min_r, boats[i].first - boats[i].second) + boats[i].second < prev_r) {
      prev_r = max(min_r, boats[i].first - boats[i].second) + boats[i].second;
    }
    //cout << (max(min_r, boats[i].first - boats[i].second) + boats[i].second) << endl;
  }
  // check for last boats
  sum++;

  cout << sum << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
