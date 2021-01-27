#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
// example: decide whether two point sets R and B can be separated by a nonvertical line
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpq ET;
// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

#define REP(i, n) for(int i = 0; i < n; ++i)

using namespace std;

void testcase() {
  // Read Input
  int a, s, b, e; cin >> a >> s >> b >> e;

  vector<K::Point_2> asteroids;
  vector<int> densities(a);
  K::Point_2 pt;
  REP(i, a) {
    cin >> pt >> densities[i];
    asteroids.push_back(pt);
  }

  vector<K::Point_2> shots;
  REP(i, s) {
    cin >> pt;
    shots.push_back(pt);
  }

  vector<K::Point_2> bounties;
  REP(i, b) {
    cin >> pt;
    bounties.push_back(pt);
  }

  // Make Triangulation on bounty hunters and set radius for each shot = dist to
  // closest bounty hunter (Actually rad = max nr < dist)
  Triangulation t;
  t.insert(bounties.begin(), bounties.end());
  vector<double> sq_radius;
  if(b > 0) {
    REP(i, s) {
      double dist = (double) CGAL::squared_distance(t.nearest_vertex(shots[i])->point(), shots[i]);
      //cout << "rad: " << dist << endl;
      sq_radius.push_back(dist);
    }
  }

  // create an LP with Ax <= b and lower bound = 0 and no upper bounds
  Program lp (CGAL::SMALLER, true, 0, true, e);

  // Make constraints that total energy < e
  REP(i, s) {
    lp.set_a(i, a, 1);
    //cout << "set_a0: " << i << " " << a << " " << 1 << endl;
  }
  lp.set_b(a, e);
  //cout << "set_b0: " << a << " " << e << endl;

  // Make constraints for each asteroid: energy of each shot is bigger than d
  REP(i, a) {
    REP(j, s) {
      double dist = CGAL::squared_distance(shots[j], asteroids[i]);
      if(b == 0 || dist < sq_radius[j]) {
        dist = max((double) 1, dist);
        lp.set_a(j, i, (double) -1 / (double) dist);
        //cout << "set_a1: " << j << " " << i << " " << -1/dist << endl;
      }
    }
    lp.set_b(i, -densities[i]);
    //cout << "set_b1: " << i << " " << -densities[i] << endl;
  }

  // solve the program, using ET as the exact type
  Solution sol = CGAL::solve_linear_program(lp, ET());
  assert(sol.solves_linear_program(lp));

  // output solution
  if(sol.is_infeasible()) cout << "n" << endl;
  else cout << "y" << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
