#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <queue>
#include <utility>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
  // Read input
  int n; cin >> n;

  vector<int> occurences(n);
  REP(i, n) {cin >> occurences[i];}

  vector<queue<int>> positions = vector<queue<int>>(n);
  REP(i, n) {
    REP(j, occurences[i]) {
      int p; cin >> p;
      positions[i].push(p);
    }
  }

  // Start Sliding window algorithm O(n * m)
  pair<int, int> min_segment;
  int min_seg_length = numeric_limits<int>::max();
  vector<int> occ_in_seg(n, 0);
  int nr_occ = 0;
  bool finish = false;

  while(!finish) {
    int min_pos = 0;
    int max_pos = 0;

    REP(i, n) {
      int cur_length = positions[i].size();

      // get current min and max positions (to find a and b)
      if(positions[min_pos].front() > positions[i].front()) {
        min_pos = i;
      }
      if(positions[max_pos].front() < positions[i].front()) {
        max_pos = i;
      }
    }
    // find a and b
    int a = positions[min_pos].front();
    int b = positions[max_pos].front();

    // find cur segment_length and check if its current shortest
    int seg_length = b - a + 1;
    if(seg_length < min_seg_length) {
      min_segment = make_pair(a, b);
      min_seg_length = seg_length;
    }

    // delete min_pos if not end else stop sliding window algorithm
    if(positions[min_pos].size() > 1) {
      positions[min_pos].pop();
    }
    else {
      finish = true;
    }
  }

  // output result
  cout << min_seg_length << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
