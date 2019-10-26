#include <iostream>
#include <vector>
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
  vector<pair<int,int>> boats(n);
  int l, p;
  for(int i = 0; i < n; ++i) {
    cin >> l >> p;
    boats[i] = make_pair(p, l);
  }

  // sort according to positions
  sort(boats.begin(), boats.end());

  /*
  for(auto elem : boats) {
    cout << "(" << elem.first << ", " << elem.second << ") ";
  }
  cout << endl;
  */

  // Loop over boats and either pick or don't pick boat
  int prev_min =  numeric_limits<int>::min();
  int prev_max =  numeric_limits<int>::max();
  int result = 0;
  for(int i = 0; i < n; ++i) {
    //cout << "info: " << prev_min << " " << prev_max << endl;
    if(prev_max <= boats[i].first) {
      result++;
      //cout << "result + 1 at " << i << endl;
      prev_min = prev_max;
      prev_max = max(prev_min + boats[i].second, boats[i].first);
    }
    else if(max(prev_min + boats[i].second, boats[i].first) < prev_max){
      prev_max = max(prev_min + boats[i].second, boats[i].first);
    }
  }
  // +1 for last boat as we can take it anyway
  cout << result + 1 << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
