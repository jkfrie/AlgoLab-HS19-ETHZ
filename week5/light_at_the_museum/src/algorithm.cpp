#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

int n, m;
int total_brightness;
vector<int> brightness;
vector<vector<pair<int,int>>> switches_half1;
vector<vector<pair<int,int>>> switches_half2;

struct Result {
	int nr_switches;
	int total_brightness;
	vector<int> switches;

  Result(int s, int b, vector<int> s2) : nr_switches(s), total_brightness(b), switches(s2) {}
};

bool operator < (const Result& r1, const Result& r2) {
  return (r1.total_brightness < r2.total_brightness);
}

vector<Result> possibilities(int halfN, const vector<vector<pair<int,int>>> &switches) {

  // Loop over all possibilities
  vector<Result> results;
  for (int s = 0; s < 1<<halfN; ++s) {
    vector<int> cur_brightnesses(m, 0);
    int sum_switches = 0;
    for(int i = 0; i < halfN; ++i) {
      if(s & 1<<i) {
        for(int j = 0; j < m; ++j){
          cur_brightnesses[j] += switches[i][j].first;
        }
      }
      else {
        ++sum_switches;
        for(int j = 0; j < m; ++j){
          cur_brightnesses[j] += switches[i][j].second;
        }
      }
    }

    // Print found solution
    for(int i = 0; i < m; ++i) {
      cout << cur_brightnesses[i] << " ";
    }
    cout << endl;

    // Check if is legal
    bool legal = true;
    for(int i = 0; i < m; ++i) {
      if(cur_brightnesses[i] > brightness[i]) {
        legal = false;
        break;
      }
    }

    // Add to result if valid
    if(legal) {
      results.push_back(Result(sum_switches, accumulate(cur_brightnesses.begin(), cur_brightnesses.end(), 0), cur_brightnesses));
      cout << sum_switches << " " << accumulate(cur_brightnesses.begin(), cur_brightnesses.end(), 0) << " " << endl;
    }
  }
  return results;
}

void testcase() {
  // Read input
  cin >> n >> m;
  brightness = vector<int>(m);
  for(int i = 0; i < m; ++i) {
    cin >> brightness[i];
  }
  total_brightness = accumulate(brightness.begin(), brightness.end(), 0);

  // Split Switches into 2 halves
  int n_firsthalf = n/2;
  int n_secondhalf = n - n_firsthalf;
  int on, off;
  switches_half1 = vector<vector<pair<int,int>>>(n_firsthalf);
  switches_half2 = vector<vector<pair<int,int>>>(n_secondhalf);
  for(int i = 0; i < n_firsthalf; ++i) {
    for(int j = 0; j < m; ++j) {
      cin >> on >> off;
      switches_half1[i].push_back(make_pair(on, off));
    }
  }

  for(int i = 0; i < n_secondhalf; ++i) {
    for(int j = 0; j < m; ++j) {
      cin >> on >> off;
      switches_half2[i].push_back(make_pair(on, off));
    }
  }

  // Get all possibilities from first half and second half
  vector<Result> result1 = possibilities(n_firsthalf, switches_half1);
  vector<Result> result2 = possibilities(n_secondhalf, switches_half2);
  sort(result2.begin(), result2.end());

  for (auto elem : result2) {
    cout << elem.total_brightness << " ";
  }
  cout << endl;

  // Binary Search over results
  int cur_switches;
  int min_switches = -1;
  bool legal = true;
  for(auto elem : result1) {
    Result target(0, total_brightness - elem.total_brightness, vector<int>());
    auto range = equal_range(result2.begin(), result2.end(), target);
    cout << range.second - range.first << endl;
		for (auto it = range.first; it != range.second; ++it) {
      for(int i = 0; i < m; ++i) {
        if(elem.switches[i] + it->switches[i] != brightness[i]) {
          legal = false;
          break;
        }
      }
      // Check if solution better than current
      if(legal && (min_switches == -1 || (elem.nr_switches + it->nr_switches < min_switches))) {
        min_switches = elem.nr_switches + it->nr_switches;
      }
    }
  }

  if (min_switches != -1) {
    cout << min_switches << endl;
  }
  else {
    cout << "impossible" << endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
