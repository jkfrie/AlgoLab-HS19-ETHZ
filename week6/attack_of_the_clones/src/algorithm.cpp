#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <map>

using namespace std;

bool cmp (const pair<int,int>& p1, const pair<int,int>& p2) {
  return (p1.second < p2.second || (p1.second == p2.second && p1.first > p2.first));
}

int find_solution(const vector<pair<int,int>>& pairs, int start, int end) {
  int result = 0;
  int prev_end = start;
  for(auto cur_elem : pairs) {
    //cout << prev_end << " " << end << endl;
    if(cur_elem.first > prev_end && cur_elem.second < end) {
      //cout << "take: " << cur_elem.first << " " << cur_elem.second << endl;
      ++result;
      prev_end = cur_elem.second;
    }
  }
  //cout << "result: " << result << endl;
  return result;
}

void testcase() {

  // Read Input
  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> jedis(n);
  map<int, int> segments;
  int a, b;

  for(int i = 0; i < n; ++i) {
    cin >> a >> b;
    // Shift b.c. of 1 index instead of 0
    --a;
    ++segments[a];
    --segments[b%m];
    --b;
    jedis[i] = make_pair(a, b);
    if(a > b)
      ++segments[0];
  }

  // Find segment that has less than 10 jedis and store overlapping jedis seperately
  int counter = 0;
  int zero_segment = 0;
  int cur_min = 11;
  vector<pair<int,int>> normal_jedis;
  vector<pair<int,int>> overlapping_jedis;

  for(auto elem : segments) {
    counter += elem.second;
    if(counter < cur_min ) {
      cur_min = counter;
      zero_segment = elem.first;
    }
  }
  //cout << "zero_segment: " << zero_segment << endl;

  // Shift segments s.t. zero_segment is at 0
  for(int i = 0; i < n; ++i) {
    a = jedis[i].first;
    b = jedis[i].second;
    a = a - zero_segment;
    if(a < 0)
      a = a + m;
    b = b - zero_segment;
    if(b <= 0)
      b = b + m;

    if(a > b) {
      //cout << "info overl: " << a << " " << b << endl;
      overlapping_jedis.push_back(make_pair(a, b));
    }
    else {
      normal_jedis.push_back(make_pair(a, b));
      //cout << "info norm: " << a << " " << b << endl;
    }
  }


  // Do regular interval selection based on earliest seg end
  sort(normal_jedis.begin(), normal_jedis.end(), cmp);
  int cur_max = find_solution(normal_jedis, -1, m);
  int result;
  for(auto elem : overlapping_jedis) {
    //cout << "overl: " << elem.first << " " << elem.second;
    result = find_solution(normal_jedis, elem.second, elem.first);
    result++;
    if(result > cur_max) {
      cur_max = result;
    }
  }

  // Output result
  cout << cur_max << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
