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

void testcase() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> next(n, -1);
  vector<int> temp(n);
  REP(i, n) cin >> temp[i];
  REP(i, n - 1) {
    int u, v;
    cin >> u >> v;
    next[u] = v;
  }

  // consider straights path (testsets 1 and 2)
  // Sliding window alg
  int dist = 1;
  multiset<int> temp_set;
  temp_set.insert(temp[0]);
  int r = 0;
  int l = 0;
  vector<int> result;
  while (next[l] != -1) {
    // cout << "l: " << l << endl;
    while (dist != m && next[r] != -1) {
      dist++;
      // cout << "dist: " << dist << endl;
      r = next[r];
      temp_set.insert(temp[r]);
    }

    // cout << "l: " << l << " r: " << r << " dist: " << dist << endl;

    // check if feasible
    // cout << "temp_set: ";
    for (auto elem : temp_set) {
      // cout << elem << " ";
    }
    // cout << endl;
    // cout << *temp_set.begin() << " " <<  *(--temp_set.end()) << endl;
    int temp_diff = abs(*temp_set.begin() - *(--temp_set.end()));
    // cout << "temp_diff: " << temp_diff << endl;
    if (temp_diff <= k && dist == m) {
      result.push_back(l);
    }

    // increase left pointer
    auto it = temp_set.find(temp[l]);
    temp_set.erase(it);
    dist--;
    l = next[l];
  }

  sort(result.begin(), result.end());
  if (result.empty())
    cout << "Abort mission";
  else {
    for (auto elem : result) {
      cout << elem << " ";
    }
  }
  cout << endl;
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) testcase();
}
