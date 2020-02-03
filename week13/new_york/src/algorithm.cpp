#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

using namespace std;

#define REP(i, n) for (int i = 0; i < n; ++i)

int n, m, k;
vector<vector<int>> adj_list;
vector<int> temperature;
vector<int> pred_map;
multiset<int> s;
vector<int> path;
set<int> result;

void is_start(int cur, int dist) {
  path.push_back(cur);
  s.insert(temperature[cur]);
  dist++;

  /*
  cout << "cur: " << cur << " dist: " << dist << endl;
  cout << "temps: ";
  for(auto elem : s) {
          cout << elem << " ";
  }
  cout << endl;
  cout << "path: ";
  for(auto elem : path) {
          cout << elem << " ";
  }
  cout << endl;
  */
  
  if(dist > m) {
    --dist;
    auto it = s.find(temperature[*(path.rbegin() + m)]);
    s.erase(it);
  }

  // check if l is start
  if (dist == m) {
    // check if temp diff is below k
    int diff = abs(*s.begin() - *(--s.end()));
    // cout << "diff: " << diff << endl;
    if (diff <= k) {
      result.insert(*(path.rbegin() + m - 1));
      //cout << "added to result" << endl;
    }
  }

  // call function on children
  for (auto child : adj_list[cur]) {
    is_start(child, dist);
  }

  // recreate stackframe from previous point
  path.pop_back();
  auto it = s.find(temperature[cur]);
  s.erase(it);

  // Check if also need to add temp of l
  if (path.size() >= m) {
    int i = path.rbegin()[m-1];
    s.insert(temperature[i]);
  }
}

void testcase() {
  cin >> n >> m >> k;
  temperature = vector<int>(n);
  adj_list = vector<vector<int>>(n);
  pred_map = vector<int>(n, -1);
  result.clear();
  REP(i, n) cin >> temperature[i];
  REP(i, n - 1) {
    int u, v;
    cin >> u >> v;
    adj_list[u].push_back(v);
    pred_map[v] = u;
  }

  // call function that traverses tree and saves all legas starts
  is_start(0, 0);

  if (result.empty())
    cout << "Abort mission"
         << "\n";
  else {
    for (auto elem : result) {
      cout << elem << " ";
    }
    cout << "\n";
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) testcase();
}
