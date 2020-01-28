#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <cmath>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VII;

int n;
int m;
int k;
VI sovereigns;
VII memo;
int turn;

// Maximum Revenue for coins l to r where persons pick before you
int max_revenue(int l, int r) {
  bool your_turn = false;
  int take_left;
  int take_right;
  int cur_val;

  //cout << "l: " << l << " r: " << r   << endl;

  // Check if memo is filled
  if(memo[l][r] > -1) {
    return memo[l][r];
  }

  // Check if its your your_turn
  if((r - l + 1) % m == turn) {
    //cout << "your turn!!" << endl;
    your_turn = true;
  }

  // Base Case
  if (r == l) {
    if(your_turn) {
      memo[l][r] = sovereigns[l];
    }
    else {
      memo[l][r] = 0;
    }
    //cout << "sol: " << memo[l][r] << endl;
    return memo[l][r];
  }

  // Recursive Case
  if(your_turn) {
    take_left = sovereigns[l] + max_revenue(l+1, r);
    take_right = sovereigns[r] + max_revenue(l, r - 1);
    cur_val = max(take_left, take_right);
  }
  else {
    cur_val = min(max_revenue(l + 1, r), max_revenue(l, r - 1));
  }
  memo[l][r] = cur_val;
  //cout << "sol: " << memo[l][r] << endl;
  return memo[l][r];
}

void testcase() {

  // Read input and do setup
  cin >> n;
  cin >> m;
  cin >> k;

  sovereigns = VI(n, 0);
  for (int i = 0; i < n; ++i)
    cin >> sovereigns[i];

  memo = VII(n, VI(n, -1));

  turn = (n - k) % m;

  // Start DP algorithm
  int result = max_revenue(0, n - 1);

  // output result
  std::cout << result << std::endl;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
