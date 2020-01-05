#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <cmath>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<double> possibilities;
vector<vector<double>> memo;
int n, k, m;

double max_prob(int day, int wealth) {
  //cout << day << " " << wealth << endl;

  // check if already calculated
  if(memo[day][wealth] > -1) {
    //cout << "memo: " << memo[day][wealth] << " " << day << "," << wealth << endl;
    return memo[day][wealth];
  }

  // check if we already have k money
  if(wealth >= m) {
    return 1.0;
  }
  // no money left
  if(wealth <= 0) {
    return 0.0;
  }
  // can we even win?
  //cout << wealth * pow(2, max(0, n-day)) << " " << max(0, n - day) << " " << wealth << endl;
  if(wealth * pow(2, max(0, n - day)) < m) {
    return 0.0;
  }

  // Find max prob for any bet from 0 - wealth
  double max_p = 0;
  for(int i = 0; i <= wealth; ++i) {
    // win on current day
    double win = possibilities[day] * max_prob(day + 1, wealth + i);
    //cout << "win: " << day << " " << wealth << " : " << win << endl;
    // loose on current day
    double loose = (1 - possibilities[day]) * max_prob(day + 1, wealth - i);
    //cout << "loose: " << day << " " << wealth << " : " << loose << endl;
    max_p = max(max_p, win + loose);
  }
  memo[day][wealth] = max_p;
  return max_p;
}

void testcase() {
  cin >> n >> k >> m;

  possibilities = vector<double>(n);
  REP(i, n) {
    cin >> possibilities[i];
  }

  memo = vector<vector<double>>(n + 2, vector<double>(m + 1, -1));
  std::cout << std::fixed << std::setprecision(5);
  cout << max_prob(0, k) << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
