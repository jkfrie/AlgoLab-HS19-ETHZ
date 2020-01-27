#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)
int N, M;

struct Result {
  int switch_count;
  int total_brightness;
  vector<int> b;

  Result(int s, int t, vector<int> br): switch_count(s), total_brightness(t), b(br) {}
};

bool operator < (const Result& r1, const Result& r2) {
return (r1.total_brightness < r2.total_brightness);
}

vector<int> brightness;

void list_results(int n, vector<Result>& results, vector<vector<pair<int,int>>>& lights) {

  for(int s = 0; s < 1<<n; ++s) {
    vector<int> zero_vec(M, 0);
    Result res(0, 0, zero_vec);
    for(int i = 0; i < n; ++i) {
      if(s & 1<<i) {
        REP(j, M) {
          res.b[j] += lights[i][j].first;
          res.total_brightness += lights[i][j].first;
        }
      }
      else {
        res.switch_count++;
        REP(j, M) {
          res.b[j] += lights[i][j].second;
          res.total_brightness += lights[i][j].second;
        }
      }
    }
    results.push_back(res);
  }

  /*
  for(auto elem : results) {
    cout << "hh ";
    for(auto e : elem.b) {
      cout << e << " ";
    }
    cout << "switch-count: " << elem.switch_count << endl;
  }
  */

}

void testcase() {
  cin >> N >> M;
  brightness = vector<int>(M);
  int tot_brightness = 0;
  REP(i, M) {
    cin >> brightness[i];
    tot_brightness += brightness[i];
  }
  int n1 = N/2; int n2 = N - n1;
  //cout << "n1" << n1 << " n2 " << n2 << endl;
  vector<vector<pair<int,int>>> lights1(N);
  vector<vector<pair<int,int>>> lights2(N);
  REP(i, N) {
    REP(j, M) {
      int on, off; cin >> on >> off;
      if(i < n1) lights1[i].push_back(make_pair(on, off));
      else lights2[i - n1].push_back(make_pair(on, off));
    }
  }

  vector<Result> results1;
  vector<Result> results2;
  list_results(n1, results1, lights1);
  list_results(n2, results2, lights2);

  // combine results with binary search
  sort(results2.begin(), results2.end());

  //cout << "sizes: " << results1.size() << " " << results2.size() << endl;

  vector<int> zero_vec(M, 0);
  int min_switches = numeric_limits<int>::max();
  for(auto elem : results1) {
    /*
    for(auto elem2 : elem.b){
      cout << elem2 << " ";
    }
    cout << endl;
    */
    Result reference(0, tot_brightness - elem.total_brightness, zero_vec);
    auto lower = std::lower_bound(results2.begin(), results2.end(), reference);
    auto upper = std::upper_bound(results2.begin(), results2.end(), reference);

    while(lower != upper) {
      bool valid = true;
      REP(j, M) {
        //cout << lower->b[j] << " ";
        if(brightness[j] != elem.b[j] + lower->b[j]) {
          valid = false;
          //break;
        }
      }
      //cout << endl;
      if(valid) min_switches = min(min_switches, elem.switch_count + lower->switch_count);
      //cout << (elem.switch_count + lower->switch_count) << endl;
      //cout << min_switches << endl;
      lower++;
    }
  }

  if(min_switches == numeric_limits<int>::max()) cout << "impossible" << endl;
  else cout << min_switches << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
