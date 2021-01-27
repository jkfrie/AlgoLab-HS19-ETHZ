#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
// example: how to solve a simple explicit LP
#include <CGAL/Gmpq.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Circle_2 S;

#define REP(i, n) for (int i = 0; i < n; ++i)

double floor_to_double(const CGAL::Quotient<ET>& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a + 1 <= x) a += 1;
  return a;
}

void testcase() {
  int n, m, c;
  cin >> n >> m >> c;

  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp(CGAL::SMALLER, true, 0, false, 0);

  int constraint = 0;

  // set max supply constraint for each warehouse
  vector<int> alcohol(n);
  REP(i, n) {
    int x, y, s;
    cin >> x >> y >> s >> alcohol[i];
    REP(j, m) { lp.set_a(i * n + j, constraint, 1); }
    lp.set_b(constraint, s);  //<= supply
    constraint++;
  }

  // set min demand constraint for each stadium
  vector<int> upper_lim(m);
  REP(j, m) {
    int x, y, d;
    cin >> x >> y >> d >> upper_lim[j];
    REP(i, n) {
      lp.set_a(i * n + j, constraint, -1);
      lp.set_a(i * n + j, constraint + 1, 1);
    }
    lp.set_b(constraint, -d);
    lp.set_b(constraint + 1, d);
    constraint += 2;
  }

  // set max alcohol constraint for each stadium
  REP(j, m) {
    REP(i, n) {
      double alc = alcohol[i];
      lp.set_a(i * n + j, constraint, alc);
    }
    lp.set_b(constraint, upper_lim[j] * 100);
    constraint++;
  }

  // read in revenues
  vector<int> revenues(n*m);
  REP(i, n) {
    REP(j, m) {
      cin >> revenues[i*n + j];
	  revenues[i*n + j] *= 100;
    }
  }

  // read in contour lines
  REP(i, c) {
    Circle_2()
    cin >> x >> y >> r;
  }

  // objective function
  REP(i, n) {
    REP(j, m) {
      lp.set_c(i * n + j, -revenues[i*n +j]);
    }
  }

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  // print the program in MPS format
  // CGAL::print_linear_program(std::cout, lp, "first_lp");
  // cout << s << endl;

  // output solution
  std::cout << std::setprecision(0);
  if (s.is_infeasible())
    cout << "RIOT!"
         << "\n";
  else
    cout << fixed << floor_to_double(-s.objective_value()) << "\n";
  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) testcase();
}
