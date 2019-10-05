#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <cmath>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;

int n,m;
int r,b;
VII adjList;
VI memo;
VI memo2;

int maxDistance(int pos);
int minDistance(int pos);

int maxDistance(int pos) {
  //std::cout << "pos max = " << pos << std::endl;
  int maxDist = -1;
  int curDist;

  // Base Cases
  if(pos == n) {
    //std::cout << "sol: " << 0 << std::endl;
    return 0;
  }

  // If case already calculated take from memory
  if (memo[pos] > -1) {
    return memo[pos];
  }

  // recursive cases
  for(auto elem : adjList[pos]) {
    curDist = minDistance(elem);
    //std::cout << "curDist max: " << curDist << std::endl;
    if(curDist > maxDist) {
      maxDist = curDist;
      //std::cout << "maxDist: " << maxDist << std::endl;
    }
  }
  //std::cout << "sol: " << maxDist + 1 << std::endl;
  memo[pos] = maxDist + 1;
  return memo[pos];
}

int minDistance(int pos) {
  //std::cout << "pos = " << pos << std::endl;
  int minDist = std::numeric_limits<int>::max();
  int curDist;

  // Base Cases
  if(pos == n) {
    return 0;
  }
  if(std::find(adjList[pos].begin(), adjList[pos].end(), n) != adjList[pos].end()) {
    //std::cout << "sol: " << 1 << std::endl;
    return 1;
  }


  // If case already calculated take from memory
  if (memo2[pos] > -1) {
    return memo2[pos];
  }

  // recursive cases
  for(auto elem : adjList[pos]) {
    curDist = maxDistance(elem);
    //std::cout << "curDist min: " << curDist << std::endl;
    if(curDist < minDist) {
      minDist = curDist;
      //std::cout << "minDist: " << minDist << std::endl;
    }
  }
  //std::cout << "sol: " << minDist + 1 << std::endl;
  memo2[pos] = minDist + 1;
  return memo2[pos];
}

void testcase() {

  // Read input and do setup
  std::cin >> n >> m;
  std::cin >> r >> b;

  adjList = VII(n, VI());
  int tmp1, tmp2;
  for (int i = 0; i < m; ++i) {
    std::cin >> tmp1 >> tmp2;
    adjList[tmp1].push_back(tmp2);
  }

  /*
  // print values
  //std::cout << "n: " << n << " m: " << m << std::endl;
  //std::cout << "r: " << r << " b: " << b << std::endl;
  for (int i = 0; i < n; ++i) {
    for(auto elem : adjList[i]) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }
  */

  // Start DP algorithm
  memo = VI(n, -1);
  memo2 = VI(n, -1);

  int result;
  int dr = minDistance(r);
  int db = minDistance(b);

  if(dr == db) {
    result = (dr % 2 == 0);
  }
  else {
    result = minDistance(r) > minDistance(b);
  }
  //std::cout << "result: " << result << std::endl;

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
