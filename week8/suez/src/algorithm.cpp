#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>
#include <limits>
#include <stdexcept>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose input type (input coefficients must fit)
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

double ceil_to_double(const CGAL::Quotient<ET>&& x) {
	double a = std::ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a-1 >= x) a -= 1;
	return a;
}

void testcase() {

  // Read input
  int n, m, h, w; cin >> n >> m >> h >> w;

  vector<pair<long, long>> new_pos(n);
  vector<pair<long, long>> old_pos(m);
  long x, y;
  REP(i, n) {
    cin >> x >> y;
    new_pos[i] = make_pair(x, y);
  }
  REP(i, m) {
    cin >> x >> y;
    old_pos[i] = make_pair(x, y);
  }

  // create an LP with Ax <= b, lower bound 1 (a >= 1) and no upper bounds
  Program lp (CGAL::SMALLER, true, 1, false, 0);

  // No overlaps with the other new posters
  int constraint_index = 0;
  REP(i, n) {
    for(int j = i + 1; j < n; ++j) {
      long d_width = 2 * abs(new_pos[i].first - new_pos[j].first);
      long d_height = 2 * abs(new_pos[i].second - new_pos[j].second);

      // Only one condition must be fulfilled, take less strict.
      if(d_width / w > d_height / h) {
        lp.set_a(i, constraint_index,  w);
        lp.set_a(j, constraint_index, w);
        lp.set_b(constraint_index, d_width);
        //cout << w << " * a" << i  << " + a" << j << " <= " << d_width << endl;
      }
      else {
        lp.set_a(i, constraint_index,  h);
        lp.set_a(j, constraint_index, h);
        lp.set_b(constraint_index, d_height);
        //cout << h << " * a" << i  << " + a" << j << " <= " << d_height << endl;
      }
      constraint_index++;
    }
  }

  // No overlaps with the old posters - find closest old poster for all
  REP(i, n) {
    long min_width = LONG_MAX;
    long min_height = LONG_MAX;
    REP(j, m) {
      long d_width = 2 * abs(new_pos[i].first - old_pos[j].first) - w;
      long d_height = 2 * abs(new_pos[i].second - old_pos[j].second) - h;
      //cout << "d_width: " << d_width << " d_height: " << d_height << endl;

      // Only one condition must be fulfilled, take less strict.
      if(d_width / w > d_height / h) {
        min_width = min(min_width, d_width);
      }
      else {
        min_height = min(min_height, d_height);
      }
    }
    //cout << "min_width: " << min_width << endl;
    //cout << "min_height: " << min_height << endl;

    // Here we have to take stricter condition!
    if(min_width / w < min_height / h) {
      lp.set_a(i, constraint_index,  w);
      lp.set_b(constraint_index, min_width);
      //cout << i << " " << min_width << endl;
    }
    else {
      lp.set_a(i, constraint_index,  h);
      lp.set_b(constraint_index, min_height);
      //cout << i << " " << min_height << endl;
    }
    constraint_index++;

    // Set objective function: sum of all aw + ah
    lp.set_c(i, -2 * (w + h));
    //cout << -2 * (w+h) << " * a" << i << endl;
  }

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));

  // output solution
  cout << setprecision(0) << fixed << ceil_to_double(-s.objective_value()) << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--)
      testcase();
}
