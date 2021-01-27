#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

#define REP(i, n) for(int i = 0; i < n; ++i)

int floor_to_double(const CGAL::Quotient<ET>& x) {
  double a = floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a + 1 <= x) a += 1;
  return a;
}

void testcase(int n, int d) {
	// create an LP with Ax <= b, lower bound 0 and no upper bounds
  	Program lp (CGAL::SMALLER, false, 0, false, 0);

	// Set constraints
	REP(i, n) {
		long norm = 0;
		REP(j, d) {
			int a; cin >> a;
			norm += a * a;
			lp.set_a(j, i, a);
		}
		int b; cin >> b;
		lp.set_a(d, i, sqrt(norm));
		lp.set_b(i, b);	
	}

	// set objective function
	lp.set_l(d, true, 0);
	lp.set_c(d, -1);

  	// solve the program, using ET as the exact type
  	Solution s = CGAL::solve_linear_program(lp, ET());
  	assert(s.solves_linear_program(lp));
  
  	// output solution
	if(s.is_infeasible()) cout << "none" << "\n";
	else if(s.is_unbounded()) cout << "inf" << "\n";
	else cout << floor_to_double(-s.objective_value()) << "\n";
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int n, d; cin >> n >> d;
	while(n) {
		testcase(n, d);
		cin >> n >> d;
	}
}
