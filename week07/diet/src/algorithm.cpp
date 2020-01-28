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

void testcase(int n, int m) {

  // create an LP with Ax <= b, lower bound 0 and no upper bounds
  Program lp (CGAL::SMALLER, true, 0, false, 0);

  // Read conditions
  int min, max;
  for(int i = 0; i < n; ++i) {
    cin >> min >> max;
    // min condition
    lp.set_b(2 * i, -min);
    // max condition
    lp.set_b(2 * i + 1, max);
  }

  int price, amount;
  for(int i = 0; i < m; ++i) {
    cin >> price;
    for(int j = 0; j < n; ++j) {
      cin >> amount;
      // min condition
      lp.set_a(i, 2 * j, -amount);
      // max condition
      lp.set_a(i, 2 * j + 1, amount);
      // set function to minimize
      lp.set_c(i, price);
    }
  }

  // solve the program, using ET as the exact type
  Solution s = CGAL::solve_linear_program(lp, ET());
  assert(s.solves_linear_program(lp));

  if(s.is_infeasible())
   cout << "No such diet." << endl;
  else
   cout << floor_to_double(s.objective_value()) << endl;

}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    while(n && m) {
      testcase(n, m);
      cin >> n >> m;
    }
}
