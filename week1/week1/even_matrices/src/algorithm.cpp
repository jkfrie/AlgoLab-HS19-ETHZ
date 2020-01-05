#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

#define REP(i, n) for(int i = 0; i < n; ++i)

using namespace std;

void testcase() {
  // Read input
  int n; cin >> n;

  // Preprocess matrix O(n²)
  vector<vector<int>> matrix = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
  REP(i, n) {
    int sum = 0;
    REP(j, n) {
      int next; cin >> next;
      sum += next;
      matrix[i + 1][j + 1] = sum;
    }
  }

  // fix columns left and right of submatrix and reduce to one dim Evenpairs.
  int counter = 0;
  REP(l, n) {
    for(int r = l; r < n; ++r) {
      int even = 0;
      int sum = 0;
      REP(i, n) {
        sum += matrix[i + 1][r + 1] - matrix[i + 1][l];
        if(sum % 2 == 0) even++;
      }
      int odd = n - even;
      counter += even;
      counter += even * (even - 1) / 2;
      counter += odd * (odd - 1) / 2;
    }
  }

  cout << counter << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
