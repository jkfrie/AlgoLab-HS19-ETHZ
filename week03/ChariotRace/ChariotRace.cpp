#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <cmath>
#include <map>
#include <tuple>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;

VVI adjacencyList;
VI cost;
int n;
VVI memo;

void minCost(int city) {

  // Base Cases
  if (adjacencyList[city].empty()) {
    memo[city][0] = cost[city];
    memo[city][1] = cost[city];
    memo[city][2] = 0;

    //std::cout << city << ": " << result[0] << ", " << result[1] << std::endl;
    return;
  }

  if (memo[city][0] > -1) {
    //std::cout << "sol: " << memo[l][r] << std::endl;
    return;
  }

  // recursive cases

  // save city from disgrace with leas cost
  int minSaveCity = -1;
  int curSaveCity = 0;
  for(auto i = adjacencyList[city].begin(); i != adjacencyList[city].end(); ++i) {
    // if not initialized
    if(memo[*i][0] == -1)
      minCost(*i);

    if(minSaveCity == -1) {
      for (auto j = adjacencyList[city].begin(); j != adjacencyList[city].end(); ++j) {
        // if not initialized
        if(memo[*j][0] == -1)
          minCost(*j);

        if(i == j) {
          curSaveCity += memo[*j][0];
          //std::cout << "curSaveCity for" << *i << ": " << curSaveCity << std::endl;
        }
        else {
          curSaveCity += std::min({ memo[*j][0], memo[*j][1] });
          //std::cout << "curSaveCity for" << *i << ": " << curSaveCity << std::endl;
        }
      }
      if(minSaveCity == -1 || minSaveCity > curSaveCity) {
        minSaveCity = curSaveCity;
        //std::cout << "minSaveCity: " << minSaveCity << std::endl;
      }
    }
    else {
      curSaveCity = curSaveCity - memo[*(i - 1)][0] + std::min({ memo[*(i - 1)][0], memo[*(i - 1)][1] });
      curSaveCity = curSaveCity + memo[*i][0] - std::min({ memo[*i][0], memo[*i][1] });
      //std::cout << "curSaveCity for" << *i << ": " << curSaveCity << std::endl;
    }

    if(minSaveCity == -1 || minSaveCity > curSaveCity) {
      minSaveCity = curSaveCity;
      //std::cout << "minSaveCity: " << minSaveCity << std::endl;
    }
  }

  // Get min for taken, notTakenNotDisgraced
  int taken = 0;
  int notTakenNotDisgraced = 0;
  for(auto elem : adjacencyList[city]) {
    taken += std::min ({ memo[elem][0], memo[elem][1], memo[elem][2] });
    notTakenNotDisgraced += std::min ({ memo[elem][0], memo[elem][1] });
  }
  memo[city][0] = cost[city] + taken;
  memo[city][1] = minSaveCity;
  memo[city][2] = notTakenNotDisgraced;

  return;
}


void testcase() {

  // Read input and do setup
  std::cin >> n;

  adjacencyList = VVI(n, VI());
  int a,b;
  for (int i = 0; i < n - 1; ++i) {
    std::cin >> a >> b;
    adjacencyList[a].push_back(b);
  }

  cost = VI(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> cost[i];
  }

  //memo[v][0 = none of them taken, 1 = parent taken, 2 = parent of parent taken]
  memo = VVI(n, VI(4, -1));

  // Start algorithm
  minCost(0);

  /*
  for(int i = 0; i < n; ++i) {
    std::cout << memo[i][0] <<", " << memo[i][1] << ", " << memo[i][2] << std::endl;
  }
  */


  // output result
  std::cout << std::min({ memo[0][0], memo[0][1] }) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
