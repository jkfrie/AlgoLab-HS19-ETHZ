#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<double> probabilities;
int n, k, m;
vector<vector<double>> memo;

double max_prob(int day, int money) {
	//cout << "day: " << day << " money: " << money << endl;

	// base cases
	if(money <= 0) {
		//cout << "return: " << 0 << endl;
		return 0;
	} 
	if(money >= m) {
		//cout << "return: " << 1 << endl;
		return 1;
	}
	if(day >= n) {
		//cout << "return: " << 0 << endl;
		return 0;
	}

	if(memo[day][money] > -1) return memo[day][money];

	// recursive cases
	double win;
	double loose;
	double maximum = 0;
	REP(i, money + 1) {
		win = probabilities[day] * max_prob(day+1, money + i);
		loose = (1.0 - probabilities[day]) * max_prob(day + 1, money - i);
		//cout << "win: " << win << " loose: " << loose << endl;
		//cout << "probabilities:  " << probabilities[day] << " day: " << day << endl;
		maximum = max(maximum, win + loose);
		//cout << "max: " << maximum << endl;
	}
	//cout << "return: " << win + loose << endl;
	memo[day][money] = maximum;
	return maximum;
}

void testcase() {
	cin >> n >> k >> m;
	probabilities = vector<double>(n);
	REP(i, n) cin >> probabilities[i];

	cout << fixed << setprecision(5);

	memo = vector<vector<double>>(n, vector<double>(m, -1));
	cout << max_prob(0, k) << "\n";

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for (int i = 0; i < t; ++i)
		testcase();
}
