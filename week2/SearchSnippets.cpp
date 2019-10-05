#include <iostream>
#include <vector>
#include <limits>
#include <numeric>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

VVI M; // word positions
VI pointers; // store pointers
VI nrWords;

void testcase() {

  // Read input and do setup
  int n; std::cin >> n;
  M = VVI(n, VI());
  nrWords = VI(n);
  pointers = VI(n, 0);

  for (int i = 0; i < n; ++i)
    std::cin >> nrWords[i];

  int tmp;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < nrWords[i]; ++j) {
      std::cin >> tmp;
      M[i].push_back(tmp);
    }
  }

  // Start DP
  VI isFinished(n, 0);
  int minLength = std::numeric_limits<int>::max();
  int curLength;
  VI max(2);
  VI min(2);
  VI minNotEnd(2);
  while (std::accumulate(isFinished.begin(), isFinished.end(), 0) < n) {

    // Calculate begin and end of interval and calculate interval length
    max[0] = -1;
    min[0] = std::numeric_limits<int>::max();
    minNotEnd[0] = std::numeric_limits<int>::max();
    for (int i = 0; i < n; ++i) {
      if (max[0] < M[i][pointers[i]]) {
        max[0] = M[i][pointers[i]];
        max[1] = i;
      }
      if (min[0] > M[i][pointers[i]]) {
        min[0] = M[i][pointers[i]];
        min[1] = i;
      }
      if (minNotEnd[0] > M[i][pointers[i]] && isFinished[i] <= 0) {
        minNotEnd[0] = M[i][pointers[i]];
        minNotEnd[1] = i;
      }
    }

    curLength = max[0] - min[0] + 1;
    //std::cout << "max: " << max[0] << " min: " << min[0] << std::endl;

    // Test if new interval smaller then best yet
    if (curLength < minLength) {
      minLength = curLength;
      //std::cout << curLength << std::endl;
    }

    // Update DP pointer
    if(pointers[minNotEnd[1]] + 1 < nrWords[minNotEnd[1]]) {
      ++pointers[minNotEnd[1]];
      //std::cout << "increased pointer " << minNotEnd[1] << " to " << pointers[minNotEnd[1]] << std::endl;
    }
    if(pointers[minNotEnd[1]] + 1 >= nrWords[minNotEnd[1]]) {
      isFinished[minNotEnd[1]] = 1;
    }
  }
  std::cout << minLength << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
