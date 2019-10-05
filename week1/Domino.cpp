#include <vector>
#include <iostream>

typedef std::vector<int> VI;

void testcase() {

  // read input
  int n; std::cin >> n;

  VI heights(n);
  int tmp;
  for(int i = 0; i < n; ++i) {
    std::cin >> tmp;
    heights[i] = tmp;
  }

  // calculate result;
  int curDist = 0;
  long result = 0;

  // check if n=0, else add beginning tile to result
  if(n >= 1) {
    ++result;
  }

  for (int i = 0; i < n - 1; ++i) {
    // check if current or new tile longer
    if(curDist - 1  < heights[i]) {
      curDist = heights[i];
    }
    else {
      curDist -= 1;
    }
    // check if larger tile hits next tile
    if(curDist > 1){
      result++;
    }
    else {
      break;
    }
  }

  // output result
  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
