#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

int n, m;
vector<vector<int>> graph;
vector<int> memo;

int turns(int position) {
  // check if result in memo
  if(memo[position] > -1) {
    if(memo[position] == 0) cout << "hää?: " << position << endl;
    return memo[position];
  }

  // Base Cases
  if(position == n) return 0;

  // Recursive Cases: loop over possible moves from position and take min
  int cur_min = numeric_limits<int>::max();
  for(auto next : graph[position]) {

    // if we can finish we should!
    if(next == n) {
      memo[position] = 1;
      return 1;
    }

    // else loop over possible moves opponent can make on next node and take max.
    int cur_max = 0;
    for(auto nextnext : graph[next]) {
      cur_max = max(cur_max, turns(nextnext));
    }

    cur_min = min(cur_min, cur_max);
  }
  memo[position] = cur_min + 2;
  return memo[position];
}

void testcase() {
  int r, b; cin >> n >> m >> r >> b;

  graph = vector<vector<int>>(n);
  REP(i, m) {
    int u, v; cin >> u >> v;
    graph[u].push_back(v);
  }

  memo = vector<int>(n + 1, -1);

  int sherlock = turns(r);
  int moriarty = turns(b);
  //cout << sherlock << " " << moriarty;

  // Output result
  if(sherlock == moriarty) cout << (sherlock % 2 == 0) << endl;
  else if(sherlock < moriarty) cout << 0 << endl;
  else cout << 1 << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
