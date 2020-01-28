#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<vector<int>> memo;
vector<vector<int>> tree;
vector<int> costs;

int min_cost(int city, int status) {
  if(memo[city][status] > -1) return memo[city][status];

  // Base Cases city is leaf
  if(tree[city].empty()) {
    //cout << "city: " << city << " " << 0 << " " << "max" << " " << costs[city] << endl;
    if(status == 0) return 0;
    if(status == 1) return numeric_limits<int>::max();
    else return costs[city];

  }

  // recursive Cases
  // status: 0 = parent taken, 1 = some child taken, 2 = current taken
  int sol0 = 0;
  int sol1 = 0;
  int sol2 = 0;

  // Easy cases status 0 & 2
  sol2 += costs[city];
  for(auto son : tree[city]) {
    int min_cost0 = min_cost(son, 0);
    int min_cost1 = min_cost(son, 1);
    int min_cost2 = min_cost(son, 2);
    sol0 += min(min_cost1, min_cost2);
    sol2 += min(min_cost0, min(min_cost1, min_cost2));
  }

  // for status 1 find cheapest son to take
  int min_sol1 = numeric_limits<int>::max();
  int tmp;
  for(auto son_taken : tree[city]) {
    int min_cost1 = min_cost(son_taken, 1);
    int min_cost2 = min_cost(son_taken, 2);
    tmp = sol0 - min(min_cost1, min_cost2) + min_cost2;
    min_sol1 = min(tmp, min_sol1);
  }
  sol1 += min_sol1;

  //cout << "city: " << city << " " << min(sol0, min(sol1, sol2)) << " " << min(sol1, sol2) << " " << sol2 << endl;
  memo[city][0] = min(sol0, min(sol1, sol2));
  memo[city][1] = min(sol1, sol2);
  memo[city][2] = sol2;
  if(status == 0) return memo[city][0];
  if(status == 1) return memo[city][1];
  else return sol2;
}

void testcase() {
  int n; cin >> n;

  tree = vector<vector<int>>(n);
  REP(i, n - 1) {
    int j, k; cin >> j >> k;
    tree[j].push_back(k);
  }

  costs = vector<int>(n);
  REP(i, n) cin >> costs[i];

  memo = vector<vector<int>>(n, vector<int>(3, -1));

  cout << min(min_cost(0, 2), min_cost(0, 1)) << endl;

}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
