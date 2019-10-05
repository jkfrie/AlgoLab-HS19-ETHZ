#include <iostream> // We will use C++ input/output via streams
#include <vector>

typedef std::vector<int> VI;

void testcase() {

  int n; std::cin >> n;

  VI vec(n);
  int tmp;
  for(int i = 0; i < n; ++i) {
    std::cin >> tmp;
    vec[i] = tmp;
  }

  int d; std::cin >> d;

  int a; int b; std::cin >> a >> b;

  vec.erase(vec.begin() + d);
  vec.erase(vec.begin() + a, vec.begin() + b + 1);

  for(int i = 0; i < vec.size(); ++i){
    std::cout << vec.at(i) << " ";
  }

  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
