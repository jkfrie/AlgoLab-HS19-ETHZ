#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

int n, m, x, k;
vector<vector<pair<int,int>>> adj_list;

int min_turns(int pos, int points, int k) {
	//cout << pos << points << endl;
	// base cases
	if(points >= x) {
		//cout << pos << " " << points << " -> ";
		//cout << 0 << endl;
		return 0;
	}
	if(k > x) return x + 1;

	// recursive cases
	if(adj_list[pos].empty()) return min_turns(0, points, k + 1);
    
	int cur_min = numeric_limits<int>::max();
	for(auto next : adj_list[pos]) {
		cur_min = min(cur_min, min_turns(next.first, points + next.second, k + 1) + 1);
	}
	//cout << pos << " " << points << " -> ";
	//cout << cur_min << endl;
    return cur_min;
}


void testcase() {
	cin >> n >> m >> x >> k;
	adj_list = vector<vector<pair<int,int>>>(n);
	REP(i, m) {
		int u, v, p; cin >> u >> v >> p;
		adj_list[u].push_back(make_pair(v, p));
	}

	/*
	for(auto line : adj_list) {
		for(auto elem: line) {
			cout << elem.first << "," << elem.second << " ";
		}
		cout << endl;
	}
	*/

	cout << min_turns(0, 0, 0) << " " << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
