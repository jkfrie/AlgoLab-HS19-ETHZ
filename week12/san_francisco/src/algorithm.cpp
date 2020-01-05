#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <utility>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<vector<pair<int,long>>> graph;
vector<vector<long>> memo;
long x;

long max_points(int hole, int turns) {

  // If we used up all k turns
  if(turns == 0) {
    return 0;
  }

  // Check if result is in memo
  if(memo[hole][turns] > -1) return memo[hole][turns];

  // Recursive cases:
  // Check if we reached a dead end
  if(graph[hole].empty()) {
    memo[hole][turns] = max_points(0, turns);
    return memo[hole][turns];
  }
  else {
    long max_t = 0;
    for(auto next_hole : graph[hole]) {
      long cur_t = max_points(next_hole.first, turns - 1) + next_hole.second;
      max_t = max(max_t, cur_t);
    }
    memo[hole][turns] = max_t;
    return max_t;
  }
}

void testcase() {
  // Read Input
  int n, m, k; cin >> n >> m >> x >> k;

  graph = vector<vector<pair<int, long>>>(n);
  REP(i, m) {
    int u, v; long p; cin >> u >> v >> p;
    graph[u].push_back(make_pair(v, p));
  }

  // Create memo
  memo = vector<vector<long>>(n, vector<long>(k + 1, -1));

  // loop over amounts of turns from 1 to k and check if max points >= x
  for(int i = 1; i <= k; ++i) {
    long result = max_points(0, i);
    //cout << "i: " << i << " res: " << result << endl;
    if(result >= x) {
      cout << i << endl;
      return;
    }
  }
  cout << "Impossible" << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
