#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
  // Read Input
  int n, m; cin >> n >> m;

  vector<int> strengths(n);
  int max_strength = 0;
  REP(i,n) {
    cin >> strengths[i];
    max_strength = max(max_strength, strengths[i]);
  }

  multiset<int, greater<int>> boxes;
  REP(i, m) {
    int w;
    cin >> w;
    if(w > max_strength) {
      cout << "impossible" << endl;
      return;
    }
    boxes.insert(w);
  }

  // Sort persons decreasing according to strength
  sort(strengths.begin(), strengths.end(), greater<int>());

  // For each round loop over all persons and take heaviest box they can carry
  int round = 0;
  while(boxes.size() > 0) {
    round ++;

    // loop over all persons and take heaviest box
    REP(i, n) {
      auto it = boxes.lower_bound(strengths[i]);
      // If there is no box for current strength end;
      if(it == boxes.end()) {
        break;
      }
      else
        //cout << "delete: " << *it << endl;
        boxes.erase(it);
    }
  }

  cout << round * 3 - 1 << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
