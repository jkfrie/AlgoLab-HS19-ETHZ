#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
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

int ceil_to_double(const CGAL::Quotient<ET>& x) {

  double a = ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a - 1 >= x) a -= 1;
  return a;
}

void testcase(int t) {
  // Read input
  int a, b;
  Solution s;
  cin >> a >> b;

  if(t == 1) {
    // create an LP with Ax <= b, lower bound 0 and no upper bounds
    Program lp (CGAL::SMALLER, true, 0, false, 0);

    // set the coefficients of A and b
    const int X = 0;
    const int Y = 1;
    lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);  //  x + y  <= 4
    lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a * b);  // 4x + 2y <= ab
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);  // -x + y <= 1
    // objective function
    lp.set_c(X, a);
    lp.set_c(Y, -b);

    // solve the program, using ET as the exact type
    s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));
  }
  else {
    // create an LP with Ax <= b, no lower bound and upper bound 0
    Program lp (CGAL::LARGER, false, 0, true, 0);

    // set the coefficients of A and b
    const int X = 0;
    const int Y = 1;
    const int Z = 2;
    lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, -4); //  x + y  >= -4
    lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_a(Z, 1, 1); lp.set_b(1, -(a * b));  // 4x + 2y + z >= -ab
    lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, -1);  // -x + y >= -1
    // objective function
    lp.set_c(X, a);
    lp.set_c(Y, b);
    lp.set_c(Z, 1);

    // solve the program, using ET as the exact type
    s = CGAL::solve_linear_program(lp, ET());
    assert(s.solves_linear_program(lp));
  }

  if(s.is_infeasible())
   cout << "no" << endl;
  else if(s.is_unbounded())
   cout << "unbounded" << endl;
  else if(t == 1)
   cout << floor_to_double(-s.objective_value()) << endl;
  else
   cout << ceil_to_double(s.objective_value()) << endl;

}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int test = 1;
    while(test) {
      cin >> test;
      if(test != 0)
       testcase(test);
    }
}
