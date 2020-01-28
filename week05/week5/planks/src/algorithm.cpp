#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

struct Square {
  long l, r, u, d;

  Square(long left, long right, long up, long down) : l(left), r(right), u(up), d(down) {}
};

bool operator < (const Square& s1, const Square& s2) {
  return (s1.r < s2.r || s1.r == s2.r && s1.l < s2.l ||
    s1.r == s2.r && s1.l == s2.l && s1.u < s2.u ||
    s1.r == s2.r && s1.l == s2.l && s1.u == s2.u && s1.d < s2.d);
}

void list_squares(vector<Square>& squares_vec, vector<int>& planks, int n, int side) {
  for(int s1 = 0; s1 < 1<<n; ++s1) {
    for(int s2 = 0; s2 < 1<<n; ++s2) {
      Square sq(0,0,0,0);
      for(int i = 0; i < n; ++i) {
        if(s1 & 1<<i) {
          if(s2 & 1<<i) sq.l += planks[i];
          else sq.r += planks[i];
        }
        else {
          if(s2 & 1<<i) sq.u += planks[i];
          else sq.d += planks[i];
        }
      }
      if(sq.r <= side && sq.l <= side && sq.u <= side && sq.d <= side) {
        squares_vec.push_back(sq);
      }
    }
  }
}

void testcase() {
  // Setup
  int n; cin >> n;
  long total_length = 0;
  int n1 = n/2; int n2 = n - n1;
  vector<int> planks1(n1); vector<int> planks2(n2);
  REP(i, n) {
    int p; cin >> p;
    if(i < n/2) planks1[i] = p;
    else planks2[i - n1] = p;
    total_length += p;
  }
  int side = total_length / 4;

  // list all possibilities for squares seperately for each split.
  vector<Square> squares1, squares2;
  list_squares(squares1, planks1, n1, side);
  list_squares(squares2, planks2, n2, side);

  // Find all combinations that fit a square
  long result = 0;
  sort(squares2.begin(), squares2.end());
  for(auto elem : squares1) {
    Square s_ref(side - elem.l, side - elem.r, side - elem.u, side - elem.d);

    auto lower = std::lower_bound(squares2.begin(), squares2.end(), s_ref);
    auto upper = std::upper_bound(squares2.begin(), squares2.end(), s_ref);
    while(lower != upper) {
      if(elem.l + lower->l <= side && elem.r + lower->r <= side &&
         elem.u + lower->u <= side && elem.d + lower->d <= side) {
          result++;
      }
      ++lower;
    }
  }

  cout << result / 24 << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
