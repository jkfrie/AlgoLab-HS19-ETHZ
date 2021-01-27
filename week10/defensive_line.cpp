#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<vector<int>> memo;

int find_max(const vector<int> &segments, const int start, const int m, const int n) {
  // Base Cases
  // If no attacker left no defenders can be attacked
  if (m == 0) {
    return 0;
  }

  // If only last defenders
  if(start > n - 1) {
    return -1;
  }

  // If we computed result allready take from memo
  if(memo[m - 1][start] != -2)
    return memo[m - 1][start];

  // Recursive Case
  int amount = segments[start];
  int rest;

  // Option1: If there is a possible segment at start
  int result1 = -1;
  if(segments[start] != -1) {
    rest = find_max(segments, start + amount, m - 1, n);
    // if strategy is legal
    if(rest != -1) result1 = amount + rest;
    else result1 = -1;
  }

  //Option2 :
  int result2;
  rest = find_max(segments, start + 1, m, n);
  // if strategy is legal
  if(rest != -1) result2 = rest;
  else result2 = -1;

  memo[m - 1][start] = max(result1, result2);
  return memo[m - 1][start];
}

void testcase() {
  // Read input
  int n, m, k; cin >> n >> m >> k;

  vector<int> defense(n);
  REP(i, n) {
    cin >> defense[i];
  }

  // Part 1: for each defender find if it is start of a legal segment and if so
  // find amount of defenders in segment.
  vector<int> segments(n, -1);
  int left = 0;
  int right = 0;
  int sum = defense[0];
  int defenders_nr = 1;
  while(left < defense.size()) {
    if(sum == k) {
      segments[left] = defenders_nr;
      sum -= defense[left];
      ++left;
      --defenders_nr;
    }
    else if(sum > k) {
      sum -= defense[left];
      ++left;
      --defenders_nr;
    }
    while(sum < k && right < defense.size() - 1 ) {
      ++right;
      sum += defense[right];
      ++defenders_nr;
    }
    if(sum < k && right == defense.size() - 1) {
      break;
    }
  }

  // Part 2: find optimal attacking strategy with DP
  memo = vector<vector<int>>(m, vector<int>(n, -2));

  int solution = find_max(segments, 0, m, n);
  if(solution == -1)
    cout << "fail" << endl;
  else
    cout << solution << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
