#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

void testcase() {
  // Read input
  int n;
  cin >> n;
  vector<int> balls(n);
  for(int i = 0; i < n; ++i) {
    cin >> balls[i];
  }

  //Adjust time of lower ball row according to timelimits of upper ball row
  for(int i = 0; i <= (n - 3) / 2; ++i) {
    balls[2*i + 1] = min(balls[2*i + 1], balls[i] - 1);
    balls[2*i + 2] = min(balls[2*i + 2], balls[i] - 1);
  }

  /*
  // print balls for debugging
  for(int i = 0; i < n; ++i) {
    cout << balls[i] << " ";
  }
  */

  // Sort vector ascending w.r.t explostion time
  sort(balls.begin(), balls.end());

  // minute counter
  string result = "yes";
  for (int i = 0; i < n; ++i) {
    if (i >= balls[i]) {
      result = "no";
      break;
    }
  }

  // Output result
  cout << result << endl;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
