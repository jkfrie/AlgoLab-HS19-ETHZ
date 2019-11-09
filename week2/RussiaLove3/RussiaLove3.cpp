#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <cmath>
#include <map>
#include <tuple>
#include <algorithm>

using std;

typedef vector<int> VI;
typedef vector<VI> VII;

int n;
int m;
int k;
VI sovereigns;
VII memo;

// Maximum Revenue for coins l to r where persons pick before you
int maxRevenue(int l, int r, int persons) {
  int cur_min = numeric_limits<int>::max();
  int take_left;
  int take_right;
  int cur_val;

  // Base Cases
  if (r - l + 1 < persons) {
    //std::cout << "sol: " << 0 << std::endl;
    return 0;
  }

  // recursive cases
  for(int i = 0; i <= persons; ++i) {
    std::cout << "l: " << l+i << " r: " << r - k + i << std::endl;
    take_left = maxRevenue(l + i + 1, r - k + i, m) + sovereigns[l + i];
    take_right = maxRevenue(l + i, r - k + i - 1, m) + sovereigns[r - k + i];
    cur_val = max(take_left, take_right);
    cur_min = min(cur_min, cur_val);
  }
  std::cout << "sol: " << curMin << std::endl;
  return cur_min;
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

  /*
  // print values
  for (int i = 0; i < n; ++i) {
    std::cout << sovereigns[i] << " ";
  }
  std::cout << std::endl;
  */

  // Start DP algorithm
  int result = maxRevenueInit(0, n - 1, k);

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
