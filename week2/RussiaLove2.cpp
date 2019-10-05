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
VII memo;

int maxRevenueInit(int l, int r);
int maxRevenue(int l, int r);

// Wait for your first turn
int maxRevenueInit(int l, int r) {
  int curMin = std::numeric_limits<int>::max();
  int curVal;

  // Base Cases
  if (r - l + 1 < k) {
    //std::cout << "sol: " << 0 << std::endl;
    return 0;
  }

  // recursive cases
  for(int i = 0; i <= k; ++i) {
    //std::cout << "l1: " << l+i << " r1: " << r - k + i << std::endl;
    curVal = maxRevenue(l + i, r - k + i);
    if(curVal < curMin) {
      curMin = curVal;
    }
  }
  //std::cout << "sol: " << curMin << std::endl;
  return curMin;
}

int maxRevenue(int l, int r) {
  int curMin1 = std::numeric_limits<int>::max();
  int curMin2 = std::numeric_limits<int>::max();
  int curVal;

  // Base Cases
  if (r - l + 1 <= 0) {
    //std::cout << "sol: " << 0 << std::endl;
    return 0;
  }

  if (memo[l][r] > -1) {
    //std::cout << "sol: " << memo[l][r] << std::endl;
    return memo[l][r];
  }

  // recursive cases
  for(int i = 0; i < m; ++i) {
    //std::cout << "l1: " << l+i+1 << " r1: " << r - m + 1 + i << std::endl;
    curVal = maxRevenue(l + i + 1, r - m + 1 + i);
    if(curVal < curMin1) {
      curMin1 = curVal;
    }
  }
  curMin1 += x[l];

  for(int i = 0; i < m; ++i) {
    //std::cout << "l2: " << l+i << " r2: " << r - m + i << std::endl;
    curVal = maxRevenue(l + i, r - m + i);
    if(curVal < curMin2) {
      curMin2 = curVal;
    }
  }
  curMin2 += x[r];

  if(curMin1 < curMin2) {
    //std::cout << "sol: " << curMin2 << std::endl;
    memo[l][r] = curMin2;
    return curMin2;
  }
  //std::cout << "sol: " << curMin1 << std::endl;
  memo[l][r] = curMin1;
  return curMin1;
}


void testcase() {

  // Read input and do setup
  std::cin >> n;
  std::cin >> m;
  std::cin >> k;


  x = VI(n, 0);
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
  int result = maxRevenueInit(0, n - 1);

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
