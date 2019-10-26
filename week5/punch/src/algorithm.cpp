#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

struct Beverage {
  int cost, volume;

  Beverage(int c, int v) : cost(c), volume(v) {}
};

struct Punch {
  int  cost, variety;

  Punch(int c, int v) : cost(c), variety(v) {}
};

bool operator < (const Punch& p1, const Punch& p2) {
  return (p1.cost < p2.cost || (p1.cost == p2.cost && p1.variety > p2.variety));
}

vector<vector<Punch>> memo;
vector<Beverage> beverages;
int n, k;
int max_volume;

Punch optimum(int i, int v) {
  //cout << "optimum(" << i << ", " << v << ")" << endl;

  int cur_amount;
  int cur_cost;

  // Look in memo
  if(memo[i][v].cost > -1) {
    return memo[i][v];
  }

  // Base cases
  if(v == 0) {
    memo[i][v] = Punch(0, 0);
    return memo[i][v];
  }
  if(i == 0) {
    cur_amount = ((v + beverages[0].volume - 1) / beverages[0].volume);
    memo[i][v] = Punch(cur_amount * beverages[0].cost, cur_amount > 0);
    return memo[i][v];
  }

  // Recursive cases
  int vol_wo = max(v - beverages[i].volume, 0);
  Punch punch1 = optimum(i, vol_wo);
  punch1.cost += beverages[i].cost;

  Punch punch2 = optimum(i-1, vol_wo);
  punch2.cost += beverages[i].cost;
  ++punch2.variety;


  Punch optimum_punch = min(punch1, punch2);

  if(v == beverages[i].volume)
    optimum_punch = min(optimum_punch, Punch(beverages[i].cost, 1));

  optimum_punch = min(optimum_punch, optimum(i - 1, v));
  memo[i][v] = optimum_punch;
  //cout << "return: " << optimum_punch.cost << ", " << optimum_punch.variety << endl;
  return memo[i][v];
}

void testcase() {
  // Read input
  cin >> n >> k;
  beverages = vector<Beverage>();
  int c, v;
  max_volume = 0;
  for(int i = 0; i < n; ++i) {
    cin >> c >> v;
    beverages.push_back(Beverage(c, v));
    max_volume = max(max_volume, v);
  }

  // Setup
  //max_volume = max_volume + k - 1;
  max_volume = k;
  memo = vector<vector<Punch>>(n, vector<Punch>(max_volume + 1, Punch(-1, 0)));

  // Call recursive function and find min for v=k until v=k-1+max_volume
  /*
  Punch min_result = Punch(numeric_limits<int>::max(), 0);
  for(int i = k; i <= max_volume; ++i) {
    Punch result = optimum(n - 1, i);
    if(result < min_result) {
      min_result = result;
    }
  }
  */
  Punch min_result = optimum(n- 1, k);

  // Print memo
  /*
  for(int i = 0; i < n; ++i) {
    for(auto elem : memo[i]) {
      cout << "(" << elem.cost << "," << elem.variety << ") ";
    }
    cout << endl;
  }
  */

  // Output result
  cout << min_result.cost << " " << min_result.variety << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
