#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <cmath>
#include <map>
#include <tuple>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;
typedef std::vector<VII> VIII;
typedef std::vector<long> VL;
typedef std::vector<VI> VVI;
typedef std::pair<int, int> TII;
typedef std::vector<TII> VT;

VI x; // word positions
int n;
int m;
int k;
int persons;
VIII memo;

int maxRevenue(int l, int r);


int maxRevenue(int l, int r, int persons) {
  int r1;
  int r2;

  // Base Cases
  if (l == r) {
    if(persons <= 0) {
      return x[r];
    }
    else {
      return 0;
    }
  }

  /*
  if (memo[l][r][persons] > -1) {
    return memo[l][r][persons];
  }
  */

  // recursive cases
  if (persons <= 0) {
    r1 = x[l] + maxRevenue(l + 1, r, m - 1);
    r2 = x[r] + maxRevenue(l, r - 1, m - 1);
    memo[l][r][persons] = std::max(r1, r2);
    return std::max(r1, r2);
  }
  else {
    r1 = maxRevenue(l + 1, r, persons - 1);
    r2 = maxRevenue(l, r - 1, persons - 1);
    memo[l][r][persons] = std::min(r1, r2);
    return std::min(r1, r2);
  }
}


void testcase() {

  // Read input and do setup
  std::cin >> n;
  std::cin >> m;
  std::cin >> k;


  x = VI(n, 0);
  for (int i = 0; i < n; ++i)
    std::cin >> x[i];

  memo = VIII(n, VII(n, VI(m, -1)));

  /*
  // print values
  for (int i = 0; i < n; ++i) {
    std::cout << x[i] << " ";
  }
  std::cout << std::endl;
  */

  // Start DP algorithm
  int result = maxRevenue(0, n - 1, k);

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
