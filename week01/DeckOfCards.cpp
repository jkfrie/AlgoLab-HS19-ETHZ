#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <limits>
#include <cmath>
#include <map>

typedef std::vector<int> VI;
typedef std::map<int, int> MP;

void testcase() {

  // read input and create partial sums with index
  int n; int k; std::cin >> n >> k;

  VI values(n, 0);
  MP partSums;
  int curSum = 0;
  int tmp;

  int curDist = std::numeric_limits<int>::max();
  int curI = 0;
  int curJ = 0;
  int tmpDist = 0;

  // Add a entry with value = 0 and i = -1
  //partSums.insert(std::make_pair(0,-1));

  for(int i = 0; i < n; ++i) {
    std::cin >> tmp;
    values[i] = tmp;
    curSum += tmp;
    if(tmp != 0) {
      partSums.insert(std::make_pair(curSum, i));
    }
    if(std::abs(k - curSum) < curDist) {
      curDist = std::abs(k - curSum);
      curI = 0;
      curJ = i;
    }
  }

  // loop over partial sum and binary search for the missing partial O(nlogn)
  for (auto elem : partSums) {
    int v_j = k + elem.first;
    //std::cout << "v_j: " << v_j << " " << "v_i: " << elem.first << std::endl;
    //std::cout << "i: " << elem.second << std::endl;
    int i = elem.second + 1;
    auto lower = partSums.lower_bound(v_j);
    //std::cout << "found this value: " << lower->first << ", " << lower->second << std::endl;
    tmpDist = std::abs(k + elem.first - lower->first);
    /*
    if(i == 92) {
      std::cout << "v_j: " << v_j << " " << "v_i: " << elem.first << std::endl;
      std::cout << "i: " << i << " j: " << lower->second << std::endl;
      std::cout << "tmpDist = " << tmpDist << std::endl;
      std::cout << values[i] << " " << values[lower->second] <<std::endl;

    }
    */

    //std::cout << "first tmpDist: " << tmpDist << std::endl;
    if ((lower->first != v_j) && (lower != partSums.begin())) {
      auto lower2 = lower;
      --lower2;
      if((std::abs(k + elem. first - lower2->first) < std::abs(k + elem.first - lower->first)) && (lower2->second >= i)) {
        std::swap(lower, lower2);
      }
    }

    //check if index j >= i
    if(lower->second < i) {
      continue;
    }

    tmpDist = std::abs(k + elem.first - lower -> first);
    //std::cout << "tmpDist = " << tmpDist << std::endl;

    // Take lexographical lower result
    if(tmpDist < curDist) {
      curI = i; curJ = lower->second; curDist = tmpDist;
    }
    else if(tmpDist == curDist && i < curI) {
      curI = i; curJ = lower->second; curDist = tmpDist;
    }
    else if(tmpDist == curDist && i == curI && lower->second < curJ) {
      curI = i; curJ = lower->second; curDist = tmpDist;
    }
  }
  // output result
  std::cout << curI << " " << curJ << std::endl;

}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
