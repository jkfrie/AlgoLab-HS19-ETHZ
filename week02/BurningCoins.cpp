#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <cmath>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;


VI x;   // coin values
int n;
VII memo;

int maxRevenue(int l, int r) {
  int r1;
  int r2;

  // Base Cases
  if (l + 1 >= r) {
      return std::max(x[l], x[r]);
  }

  // If case already calculated take from memory
  if (memo[l][r] > -1) {
    return memo[l][r];
  }

  // recursive cases
  r1 = x[l] + std::min(maxRevenue(l + 2, r), maxRevenue(l + 1, r - 1));
  r2 = x[r] + std::min(maxRevenue(l + 1, r - 1), maxRevenue(l, r - 2));
  memo[l][r] = std::max(r1, r2);
  return memo[l][r];
}


void testcase() {

  // Read input and do setup
  std::cin >> n;

  x = VI(n);
  for (int i = 0; i < n; ++i)
    std::cin >> x[i];

  memo = VII(n, VI(n, -1));

  /*
  // print values
  for (int i = 0; i < n; ++i) {
    std::cout << x[i] << " ";
  }
  std::cout << std::endl;
  */

  // Start DP algorithm
  int result = maxRevenue(0, n - 1);

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
