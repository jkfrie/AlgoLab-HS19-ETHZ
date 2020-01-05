#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

int n, m, k;
vector<int> sovereigns;
vector<vector<int>> memo;

int max_winnings(int l, int r) {
  // check if sol is in memo
  if(memo[l][r] > -1) return memo[l][r];

  // Determine if it is your turn
  bool your_turn = (n - k) % m == (r - l + 1) % m;

  // Base Cases
  if(l == r) return (your_turn ? sovereigns[l] : 0);

  // Recursive Cases
  int sol;
  if(your_turn) {
    sol = max(sovereigns[l] + max_winnings(l + 1, r), sovereigns[r] + max_winnings(l, r - 1));
  }
  else {
    sol = min(max_winnings(l + 1, r), max_winnings(l, r - 1));
  }
  memo[l][r] = sol;
  return sol;
}

void testcase() {
  cin >> n >> m >> k;

  sovereigns = vector<int>(n);
  REP(i, n) cin >> sovereigns[i];

  memo = vector<vector<int>>(n, vector<int>(n, -1));

  cout << max_winnings(0, n - 1) << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
