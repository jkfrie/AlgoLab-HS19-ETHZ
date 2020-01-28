#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<pair<int,int>> beverages;
vector<vector<pair<int,int>>> memo;

// Return pair (cost, variety)
pair<int,int> optimum(int i, int vol) {
  // check if result already exists
  if(memo[i][vol].first < numeric_limits<int>::max()) return memo[i][vol];

  int cur_cost = beverages[i].first;
  int cur_vol = beverages[i].second;
  pair<int,int> sol = make_pair(numeric_limits<int>::max(), 0);

  // base Cases
  if(i <= 0) {
    if(vol <= cur_vol) {
      //cout << i << " " << vol << ": " << cur_cost << " " << numeric_limits<int>::max() - 1 << endl;
      memo[i][vol] = make_pair(cur_cost, numeric_limits<int>::max() - 1);
      return memo[i][vol];
    }
    else {
      sol = optimum(i, vol - cur_vol);
      sol.first += cur_cost;
      //cout << i << " " << vol << ": " << sol.first << " " << sol.second << endl;
      memo[i][vol] = sol;
      return sol;
    }
  }

  if(vol <= cur_vol) {
    pair<int,int> tmp = optimum(i - 1, vol);
    sol = min(tmp, make_pair(cur_cost, numeric_limits<int>::max() - 1));
    //cout << i << " " << vol << ": " << sol.first << " " << sol.second << endl;
    memo[i][vol] = sol;
    return sol;
  }

  // Recursive cases
  sol = optimum(i-1, vol);

  if(vol >= cur_vol) {
    pair<int,int> tmp = optimum(i - 1, vol - cur_vol);
    tmp.second--;
    tmp.first += cur_cost;
    sol = min(sol, tmp);

    tmp = optimum(i, vol - cur_vol);
    tmp.first += cur_cost;
    sol = min(sol, tmp);
  }
  //cout << i << " " << vol << ": " << sol.first << " " << sol.second << endl;
  memo[i][vol] = sol;
  return sol;
}

void testcase(){
  int n, k; cin >> n >> k;

  beverages = vector<pair<int,int>>(n);
  REP(i, n) {
    int c, v; cin >> c >> v;
    beverages[i] = make_pair(c, v);
  }

  memo = vector<vector<pair<int,int>>>(n, vector<pair<int,int>>(k + 1, make_pair(numeric_limits<int>::max(), 0)));
  pair<int, int> result = optimum(n - 1, k);
  cout << result.first << " " << numeric_limits<int>::max() - result.second << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
