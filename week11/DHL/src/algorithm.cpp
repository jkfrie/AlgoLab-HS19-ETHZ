#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
  // Read input
  int n; cin >> n;
  vector<int> left(n);
  vector<int> right(n);
  REP(i, n) cin >> left[i];
  REP(i, n) cin >> right[i];

  // Go through all possibilities of splitting left and right into multiple parts
  // and add vector of the (S - k) of each split a vector of solutions for i splits
  //*******************************************************************************
  // 1st dim of sol_left and sol_right vector corresponds to amount of splits
  // 2nd dim corresponds to different solutions with same amount of splits
  // 3rd dim corresponds to the (S-k) values of each splits

  vector<vector<vector<long long>>> sol_left(n);
  vector<vector<vector<long long>>> sol_right(n);

  // A split between parcel i and i+1 means that parcel i+1 is taken in tis round
  // and i in next round. Loop over all possible combinations of splits:
  for(int s = 0; s < 1<<(n-1); ++s) {
    long long sum_left = 0;
    long long sum_right = 0;
    int count = 0;
    int total_splits = 0;
    vector<long long> sums_left;
    vector<long long> sums_right;

    for(int i = 0; i < n; ++i) {
      sum_left += left[i];
      sum_right += right[i];
      count++;

      // Check if there is a split and if so save and reset sum and count values.
      // after last parcel we make a split anyway!
      if(s & 1<<i || i == n-1) {
        total_splits++;
        sums_left.push_back(sum_left - count);
        sum_left = 0;
        sums_right.push_back(sum_right - count);
        sum_right = 0;
        count = 0;
      }
    }

    // store sums_left and sums_right according to total_count
    sol_left[total_splits - 1].push_back(sums_left);
    sol_right[total_splits - 1].push_back(sums_right);
  }

  // Take all combinations of solutions and calculate min cost.
  // only constraint is, that the both left and right need same nr of splits,
  // s.t. they finish at same time!
  long long min_cost = numeric_limits<long long>::max();
  REP(i, n) {
    for(auto l : sol_left[i]) {
      for(auto r : sol_right[i]) {
        long long cost = 0;
        REP(j,i + 1) {
          cost += l[j] * r[j];
        }
        min_cost = min(min_cost, cost);
      }
    }
  }

  // Output solution
  cout << "min cost: " << min_cost << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
