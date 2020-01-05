#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
  // Read Input
  int n; cin >> n;

  // Loop over tiles and check if it topples
  int h;
  int max_range = 2; // make sure first tile is toppled
  int counter = 0;
  REP(i, n) {
    cin >> h;

    max_range--;
    if(max_range > 0) {
      max_range = max(max_range, h);
      counter++;
    }
  }

  cout << counter << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
