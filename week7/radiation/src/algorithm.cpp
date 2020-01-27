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
typedef long IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

struct Position{
    int x;
    int y;
    int z;

    Position(int x, int y, int z) : x(x), y(y), z(z) {}
};

void power_vector(vector<double> &vec, int x, int d) {
  vec[0] = 1;
  for(int i = 1; i <= d; ++i) {
    vec[i] = vec[i - 1] * x;
  }
}
bool check(const int d, const vector<Position> &healthy, const vector<Position> &tumor) {

  // create an LP with Ax <= b, no lower and upper bounds
  Program lp (CGAL::SMALLER, false, 0, false, 0);

  // loop over all healthy points
  int point_index = 0;
  int epsilon_index = 0;
  for(auto point : healthy) {
    int var_index = 1;

    // Vectors to store x^i, y^i and z^i.
    vector<double> x_degree(d + 1); power_vector(x_degree, point.x, d);
    vector<double> y_degree(d + 1); power_vector(y_degree, point.y, d);
    vector<double> z_degree(d + 1); power_vector(z_degree, point.z, d);

    // loop over all polynomial components
    REP(i, d + 1) {
      REP(j, d + 1 - i) {
        REP(k, d + 1 - i - j) {
          lp.set_a(var_index, point_index,  x_degree[i] * y_degree[j] * z_degree[k]);
          //cout << "set a: " << var_index << " " << point_index << " " << x_degree[i] * y_degree[j] * z_degree[k] << endl;
          var_index++;
        }
      }
    }

    lp.set_a(epsilon_index, point_index, 1);
    lp.set_b(point_index, 0);
    point_index++;
  }

  // loop over all tumor points
  for(auto point : tumor) {
    int var_index = 1;
    // Vectors to store x^i, y^i and z^i.
    vector<double> x_degree(d + 1); power_vector(x_degree, point.x, d);
    vector<double> y_degree(d + 1); power_vector(y_degree, point.y, d);
    vector<double> z_degree(d + 1); power_vector(z_degree, point.z, d);

    // loop over all polynomial components
    REP(i, d + 1) {
      REP(j, d + 1 - i) {
        REP(k, d + 1 - i - j) {
          lp.set_a(var_index, point_index,  -1 * x_degree[i] * y_degree[j] * z_degree[k]);
          //cout << "set a: " << var_index << " " << point_index << " " << -1 * x_degree[i] * y_degree[j] * z_degree[k] << endl;
          var_index++;
        }
      }
    }
    lp.set_a(epsilon_index, point_index, 1);
    //cout << "set a: " << epsilon_index << " " << point_index << " " << 1 << endl;
    lp.set_b(point_index, 0);
    //cout << "set_b: " << point_index << " " << 0 << endl;
    point_index++;
  }

  // Make sure every point is epsilon appart from polynomial line and maximize epsilon
	lp.set_c(epsilon_index, -1.0);
	lp.set_l(epsilon_index, true, 0.0);
	lp.set_u(epsilon_index, true, 1.0);

  CGAL::Quadratic_program_options options;
	options.set_pricing_strategy(CGAL::QP_BLAND);
	Solution s = CGAL::solve_linear_program(lp, ET(), options);
	assert (s.solves_linear_program(lp));
	// cout << s << endl;
	return !s.is_infeasible() && (s.objective_value() != 0);
}


void testcase() {

  // Read input
  int h, t; cin >> h >> t;

  int x, y, z;
  vector<Position> healthy;
  REP(i, h) {
    cin >> x >> y >> z;
    healthy.push_back(Position(x, y, z));
  }
  vector<Position> tumor;
  REP(i, t) {
    cin >> x >> y >> z;
    tumor.push_back(Position(x, y, z));
  }

  // loop over all d <= 30 and set up lp
  for(int d = 0; d <= 30; ++d) {
    if(check(d, healthy, tumor)) {
      cout << d << endl;
      return;
    }
  }
  cout << "Impossible!" << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    while(n--) {
      testcase();
    }
}
