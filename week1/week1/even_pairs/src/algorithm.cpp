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

  // Count nr of odd and even numbers
  int sum = 0;
  int odd = 0;
  int even = 0;
  REP(i, n) {
    int next; cin >> next;
    sum += next;

    if(sum % 2 == 0) even++;
    else odd++;
  }

  // Compute result
  long result = even;
  result += even * (even - 1) / 2;
  result += odd * (odd - 1) / 2;
  cout << result << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
