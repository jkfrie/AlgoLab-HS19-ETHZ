#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <cmath>

using namespace std;

#define REP(i,n) for(int i = 0; i < n; ++i)

void testcase() {
  // Read input
  int n, k; cin >> n >> k;

  vector<int> deck(n);
  REP(i, n) {cin >> deck[i];}

  // Sliding window algorithm
  int right = 0;
  pair<int, int> best;
  int cur_val = k;
  int sum = deck[0];
  for(int left = 0; left < n; ++left) {
    //cout << "left: " << left  << " sum: " << sum << endl;

    // Check if found better value
    if(abs(k - sum) < cur_val) {
      cur_val = abs(k -sum);
      best = make_pair(left, right);
    }

    // move right pointer
    while(sum < k && right < n - 1) {
      ++right;
      sum += deck[right];
      //cout << "right: " << right  << " sum: " << sum << endl;

      // Check if found better value
      //cout << abs(k - sum) << endl;
      if(abs(k - sum) < cur_val) {
        cur_val = abs(k -sum);
        best = make_pair(left, right);
      }
    }

    // reduce sum as left pointer moves one position
    sum -= deck[left];
  }

  cout << best.first << " " << best.second << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
