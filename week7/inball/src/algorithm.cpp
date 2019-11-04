#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <utility>
#include <stdexcept>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

int floor_to_double(const CGAL::Quotient<ET>& x) {
  double a = floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a + 1 <= x) a += 1;
  return a;
}

void testcase(int n) {
  int d;
  cin >> d;

  // create an LP with Ax <= b, no lower bound and no upper bounds
  Program lp (CGAL::SMALLER, false, 0, false, 0);

  // Read conditions
  int a, b;
  for(int i = 0; i < n; ++i) {
    int norm = 0;
    for(int j = 0; j < d; ++j) {
      cin >> a;
      norm += a * a;
      // Set ineualities
      lp.set_a(j, i, a);
    }
    // Add d * norm to the inequality where d is distance
    lp.set_a(d, i, sqrt(norm));

    // Set right side of inequalities
    cin >> b;
    lp.set_b(i, b);
  }

  // Set function to minimize and make d >= 0
  lp.set_l(d, true, 0);
  lp.set_c(d, -1);

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));

  if(s.is_infeasible())
   cout << "none" << endl;
  else if(s.is_unbounded())
   cout << "inf" << endl;
  else
   cout << floor_to_double(-s.objective_value()) << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while(n) {
      testcase(n);
      cin >> n;
    }
}
