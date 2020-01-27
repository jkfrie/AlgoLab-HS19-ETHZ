#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;
#define REP(i, n) for(int i = 0; i < n; ++i)

bool custom_sort(pair<int,int> p1, pair<int,int> p2) {
	return (p1.second < p2.second || (p1.second == p2.second && p1.first > p2.first));
}

void testcase() {
	int n, m; cin >> n >> m;
	vector<pair<int,int>> jedis(n);
	vector<int> segment_count(m, 0);
	REP(i, n) {
		int a, b; cin >> a >> b;
		--a; --b;
		jedis[i] = (make_pair(a, b));
		if(a <= b) {
			++segment_count[a];
			if(b != m-1) --segment_count[b+1];

		}
		else {
			++segment_count[0];
			--segment_count[b+1];
			++segment_count[a];
		}
	}
	/*
	cout << "segment_count:" << endl;
	for(auto elem : segment_count) {
		cout << elem << " ";
	}
	cout << endl;
	*/

	// count nr of jedis in each segment;
	int jedi_count = 0;
	int small_segment;
	REP(i, m) {
		jedi_count += segment_count[i];

		if(jedi_count <= 10) {
			small_segment = i;
			//cout << "small_segment" << jedi_count << endl;
			break;
		}
	}

	// shift the (a,b) pairs of all jedis s.t. small segment is at 0
	vector<pair<int,int>> special_jedis;
	vector<pair<int,int>> normal_jedis;
	REP(i, n) {
		jedis[i].first -= small_segment;
		if(jedis[i].first < 0) jedis[i].first = m + jedis[i].first;
		jedis[i].second -= small_segment;
		if(jedis[i].second < 0) jedis[i].second = m + jedis[i].second;

		if(jedis[i].first > jedis[i].second || jedis[i].first == 0) {
			special_jedis.push_back(make_pair(jedis[i].first, jedis[i].second));
		}
		else normal_jedis.push_back(make_pair(jedis[i].first, jedis[i].second));
	}


	// for each jedi that protects segment 0 run greedy algorithm
	sort(normal_jedis.begin(), normal_jedis.end(), custom_sort);

	cout << jedis.size() << endl;
	cout << "special:" << endl;
	cout << special_jedis.size() << endl;

	cout << "normal:" << endl;
	cout << normal_jedis.size() << endl;

	int max_sol = -1;
	for(auto elem : special_jedis) {
		int cur_sol = 0;
		int l = elem.second;
		int r;
		if(elem.first != 0) r = elem.first;
		else r = m;

		for(auto elem2 : normal_jedis) {
			if(elem2.first > l && elem2.second < r) {
				l = elem2.second;
				cur_sol++;
			}
		}
		max_sol = max(max_sol, cur_sol + 1);
	}

	int cur_sol = 0;
		int l = -1;
		int r = m;
		for(auto elem2 : normal_jedis) {
			if(elem2.first > l && elem2.second < r) {
				l = elem2.second;
				cur_sol++;
			}
		}
		max_sol = max(max_sol, cur_sol);

	cout << max_sol << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
