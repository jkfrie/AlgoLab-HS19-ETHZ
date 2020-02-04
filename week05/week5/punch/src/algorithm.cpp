#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;
vector<int> costs;
vector<int> volumes;

#define REP(i, n) for(int i = 0; i < n; ++i)

void testcase() {
    int n, k; cin >> n >> k;
    costs = vector<int>(n);
    volumes = vector<int>(n);
    REP(i, n) cin >> costs[i] >> volumes[i];

    // Rows of memo = volume and columns = drink i
    vector<vector<pair<int,int>>> memo(k);
    REP(cur_drink, n+1) {
        REP(cur_vol, k+1) {
            // if cur_vol is zero c and v are also zero
            if(cur_vol == 0) memo[cur_drink].push_back(make_pair(0, 0));

            // if we dont use any drink
            else if(cur_drink == 0){
                memo[cur_drink].push_back(make_pair(numeric_limits<int>::max(), 0));
            }

            // recursive cases
            else{

                pair<int,int> sol1, sol2, sol3;
                sol1 = memo[cur_drink][max(0, cur_vol - volumes[cur_drink])];
                sol1.first += costs[cur_drink];
                if(cur_vol - volumes[cur_drink] <= 0) ++sol1.second;

                sol2 = memo[cur_drink - 1][max(0, cur_vol - volumes[cur_drink])];
                sol2.first += costs[cur_drink];
                ++sol2.second;

                sol3 = memo[cur_drink][cur_vol];

                memo[cur_drink][cur_vol] = min(sol1, min(sol2, sol3));
            }

        }
    }

    // print memo
    for(auto line : memo){
        for(auto elem : line) {
            cout << elem << "  ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}