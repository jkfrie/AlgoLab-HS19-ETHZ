#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

struct Plank {
  long u, r, d, l;
};

bool operator < (const Plank& p1, const Plank& p2) {
  //cout << "less than function used" << endl;
  return (p1.u < p2.u || (p1.u == p2.u && p1.r < p2.r) ||
          (p1.u == p2.u && p1.r == p2.r && p1.d < p2.d) ||
          (p1.u == p2.u && p1.r == p2.r && p1.d == p2.d && p1.l < p2.l));
}

void compute(const vector<int> &lengths, int from, int n, vector<Plank> &out, long sideLength) {
  // Loop over all Possibilities
  for(int s1 = 0; s1 < 1<<n; ++s1) {
    for(int s2 = 0; s2 < 1<<n; ++s2) {
      Plank p = {0, 0, 0, 0};
      for(int i = 0; i < n; ++i) {
        if(s1 & 1<<i) {
          if(s2 & 1<<i)
            p.u += lengths[from + i];
          else
            p.r += lengths[from + i];
        }
        else {
          if(s2 & 1<<i)
            p.d += lengths[from + i];
          else
            p.l += lengths[from + i];
        }
      }

      // Check if this is acceptable solution
      if(p.u <= sideLength && p.r <= sideLength && p.d <= sideLength && p.l <= sideLength) {
        out.push_back(p);
        //cout << from << " found: " << p.u << p.r << p.d << p.l << endl;
      }
    }
  }

}

void testcase() {
  // Read input
  int n;
  int totalLength = 0;
  cin >> n;
  vector<int> lengths(n);
  for(int i = 0; i < n; ++i) {
    cin >> lengths[i];
    totalLength += lengths[i];
  }

  // Early stop if no possible solution
  if (totalLength % 4 != 0) {
		cout << 0 << endl;
		return;
	}

  // Split up the dataset into 2 halves & compute possible side lengths
  long sideLength = totalLength / 4;
  int halfN = n / 2;
  vector<Plank> firstHalf;
	vector<Plank> secondHalf;
  random_shuffle(lengths.begin(), lengths.end());

	compute(lengths, 0, halfN, firstHalf, sideLength);
	compute(lengths, halfN, n - halfN, secondHalf, sideLength);

  // Sort secondHalf and do binary search
  sort(secondHalf.begin(), secondHalf.end());

  /*
  for(auto elem : secondHalf) {
    cout << "first elem: " << elem.u << elem.r << elem.d << elem.l << endl;
  }
  */

  long result = 0;
  for(auto p : firstHalf) {
    Plank query = {sideLength - p.u, sideLength - p.r, sideLength - p.d, sideLength - p.l};
    auto lower = std::lower_bound(secondHalf.begin(), secondHalf.end(), query);
    auto upper = std::upper_bound(secondHalf.begin(), secondHalf.end(), query);
    //cout << "Bounds: " << upper << "/" << lower << endl;
    result += upper - lower;
  }

  cout << result / 24 << endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
