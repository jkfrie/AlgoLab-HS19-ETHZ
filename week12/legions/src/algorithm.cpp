#include <CGAL/Gmpz.h>
#include <CGAL/QP_functions.h>
#include <CGAL/QP_models.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

#define REP(i, n) for (int i = 0; i < n; ++i)

double floor_to_double(const CGAL::Quotient<ET>& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcase() {

  long init_x, init_y; int n; cin >> init_x >> init_y >> n;

  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp(CGAL::SMALLER, false, 0, false, 0);

  const int X = 0;
  const int Y = 1;
  const int D = 2;
  int index = 0;
  REP(i, n) {
	  int a, b, c, v; cin >> a >> b >> c >> v;
	  double norm = sqrt(a*a + b*b);
	  lp.set_a(X, index, a);
	  lp.set_a(Y, index, b);
	  lp.set_a(D, index, norm);
	  lp.set_b(index, -c);
	  index++;
  }

  lp.set_l(D, true, 0); 
  // objective function
  lp.set_c(D, -1);  

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));

  // output solution
  std::cout << floor_to_double(CGAL::to_double(-s.objective_value())) << endl;

  return;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) testcase();
}
