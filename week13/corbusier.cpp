#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<vector<int>> memo;

int possible(vector<long> &heights, int r, int i, int k) {
	if(memo[r][i] > -1) return memo[r][i];

	//cout << "possible: " << r << " " << i << endl;
	// base cases
	if(r==0) {
		//cout << (heights[0] % k == i) << endl;
		memo[r][i] = heights[0] % k == i;
		return memo[r][i];
	}

	// recursive cases
	int mod = heights[r] % k;
	mod = i - mod;
	if(mod < 0) mod = k + mod;
	//cout << "mod: " << mod << endl;
	int sol1 = possible(heights, r-1, mod, k);
	int sol2 = possible(heights, r-1, i, k);
	//cout << (sol1 || sol2) << endl;
	memo[r][i] = (sol1 || sol2);
	return memo[r][i];
}

void testcase() {
	int n, i, k; cin >> n >> i >> k;
	vector<long> heights(n);
	REP(i, n) cin >> heights[i];

	memo = vector<vector<int>>(n, vector<int>(k, -1));
	if(possible(heights, n-1, i, k)) cout << "yes" << "\n";
	else cout << "no" << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
