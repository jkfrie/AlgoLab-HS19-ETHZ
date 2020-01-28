#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<int> a;
vector<int> b;
vector<vector<long>> memo;

long min_cost(int l, int r) {
	//cout << l << " " << r << endl;
	
	// base cases
	if((l<0 && r>=0) || (r<0 && l>=0)) return numeric_limits<int>::max();
	else if(l<0 && r<0) return 0;

	if(memo[l][r] > -1) {return memo[l][r];}
	//cout << l << " " << r << endl;

	// Recursive Cases: we see that we only take multiple parcels from
	// one side but never multiple parcels from both as this is always 
	// suboptimal!
	long cost = a[l] * b[r]; 
	long cur_min = cost + min(min_cost(l-1,r-1), min(min_cost(l-1,r), min_cost(l,r-1)));
	memo[l][r] = cur_min;
	return cur_min;
}

void testcase() {
	int n; cin >> n;
	a = vector<int>(n);
	b = vector<int>(n);
	REP(i, n) {cin >> a[i]; --a[i];}
	REP(i, n) {cin >> b[i]; --b[i];}
	
	memo = vector<vector<long>>(n, vector<long>(n, -1));
	cout << min_cost(n-1, n-1) << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
