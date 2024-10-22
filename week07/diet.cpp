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

void testcase(int n, int m) {
  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp (CGAL::SMALLER, true, 0, false, 0); 

  // set bounds
  REP(i, n) {
	  int a, b;
	  cin >> a >> b;
	  lp.set_b(i, -a);
	  lp.set_b(i + n, b);
  }

  // set sums of nutrients of each food and objective function
  vector<int> prices(m);
  REP(i, m) {
	  cin >> prices[i];
	  lp.set_c(i, prices[i]);
	  REP(j, n) {
		  int amount; cin >> amount;
		  lp.set_a(i, j, -amount);
		  lp.set_a(i, j + n, amount);
	  }
  }

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));
  
  // output solution
  if(s.is_infeasible()) cout << "No such diet." << "\n";
  else cout << floor_to_double(s.objective_value()) << "\n"; 
  return;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	while(n > 0) {
		testcase(n, m);
		cin >> n >> m;
	}
}
