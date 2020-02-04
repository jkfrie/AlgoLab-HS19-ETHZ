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
    vector<vector<pair<int,int>>> memo(n+1, vector<pair<int,int>>(k+1, make_pair(numeric_limits<int>::max(), numeric_limits<int>::max())));
    REP(cur_drink, n+1) {
        REP(cur_vol, k+1) {
            // if cur_vol is zero c and v are also zero
            if(cur_vol == 0) memo[cur_drink][cur_vol] = make_pair(0, numeric_limits<int>::max());

            // if we dont use any drink
            else if(cur_drink == 0){
                memo[cur_drink][cur_vol] = make_pair(numeric_limits<int>::max(), numeric_limits<int>::max());
            }

            // recursive cases
            else{
                pair<int,int> sol1, sol2, sol3;
                sol1 = memo[cur_drink][max(0, cur_vol - volumes[cur_drink - 1])];
                if(sol1.first < numeric_limits<int>::max()) sol1.first += costs[cur_drink - 1];
                if(cur_vol - volumes[cur_drink - 1] <= 0) --sol1.second;

                sol2 = memo[cur_drink - 1][max(0, cur_vol - volumes[cur_drink - 1])];
                if(sol2.first < numeric_limits<int>::max()) sol2.first += costs[cur_drink - 1];
                --sol2.second;

                sol3 = memo[cur_drink - 1][cur_vol];

                memo[cur_drink][cur_vol] = min(sol1, min(sol2, sol3));

            }

        }
    }

    // print memo
	/*
    REP(i, n+1) {
		REP(j, k+1) {
            cout << memo[i][j].first << "," << numeric_limits<int>::max() - memo[i][j].second << " ";
        }
        cout << endl;
    }
	*/

	cout << memo[n][k].first << " " << numeric_limits<int>::max() - memo[n][k].second << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
