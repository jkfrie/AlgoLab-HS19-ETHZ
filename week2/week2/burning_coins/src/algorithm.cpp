#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<int> coins;
vector<vector<int>> memo;

int optimal_value(int l, int r) {
  // Check if sol is in memo
  if(memo[l][r] > -1) {
    return memo[l][r];
  }

  // Base Cases
  if(r - l < 0) return 0;
  if(r - l == 0) return coins[l];
  if(r - l == 1) return max(coins[l], coins[r]);

  // Recursive Cases
  int take_left = coins[l] + min(optimal_value(l+1, r-1), optimal_value(l+2, r));
  int take_right = coins[r] + min(optimal_value(l+1, r-1), optimal_value(l, r-2));
  memo[l][r] = max(take_left, take_right);
  return memo[l][r];
}

void testcase() {
  // Read Input
  int n; cin >> n;

  coins = vector<int>(n);
  REP(i, n) cin >> coins[i];

  memo = vector<vector<int>>(n, vector<int>(n,-1));
  cout << optimal_value(0, n - 1) << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
