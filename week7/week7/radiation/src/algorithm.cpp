#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include <CGAL/Gmpz.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>

using namespace std;

// choose input type (input coefficients must fit)
typedef double IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

#define REP(i, n) for (int i = 0; i < n; ++i)

vector<vector<int>> healthy;
vector<vector<int>> tumor;
int h, t;

bool valid_d(int d) {
  // create an LP with Ax <= b and no lower/upper bounds
  Program lp(CGAL::SMALLER, false, 0, false, 0);
  int var_index = 1;
  REP(degx, d + 1) {
    for (int degy = 0; degy + degx < d + 1; ++degy) {
      for (int degz = 0; degz + degy + degx < d + 1; ++degz) {
        // set left sides of healthy cells
        REP(i, h) {
          double var = pow(healthy[i][0], degx) * pow(healthy[i][1], degy) *
                     pow(healthy[i][2], degz);
          lp.set_a(var_index, i, var);
        }
        // set left sides of tumor cells
        REP(i, t) {
          double var = pow(tumor[i][0], degx) * pow(tumor[i][1], degy) *
                     pow(tumor[i][2], degz);
          lp.set_a(var_index, h + i, -var);
        }
        ++var_index;
      }
    }
  }

  // set additional variable alpha that we add s.t. no cell is on border
  // and set right sides.
  REP(i, h) { lp.set_a(0, i, 1); }
  REP(i, t) { lp.set_a(0, h + i, 1); }

  // set additional variable to > 1
  lp.set_l(0, true, 0);
  lp.set_u(0, true, 1);
  lp.set_c(0, -1);

  //solve the program, using ET as the exact type
  CGAL::Quadratic_program_options options;
  options.set_pricing_strategy(CGAL::QP_BLAND);
  Solution s = CGAL::solve_linear_program(lp, ET(), options);
  assert(s.solves_linear_program(lp));
  return !s.is_infeasible() && s.objective_value() != 0;
}

void testcase() {
  cin >> h >> t;
  healthy = vector<vector<int>>(h, vector<int>(3));
  tumor = vector<vector<int>>(t, vector<int>(3));
  REP(i, h) { cin >> healthy[i][0] >> healthy[i][1] >> healthy[i][2]; }
  REP(i, t) { cin >> tumor[i][0] >> tumor[i][1] >> tumor[i][2]; }

  // output solution
  for (int i = 0; i <= 30; ++i) {
    if (valid_d(i)) {
      cout << i << "\n";
      return;
    }
  }
  cout << "Impossible!" << "\n";
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) testcase();
}
