#include <iostream> // We will use C++ input/output via streams
#include <string>
#include <iomanip>

void testcase() {

  int a; std::cin >> a; // Read the next number
  long b; std::cin >> b;
  std::string c; std::cin >> c;
  double d; std::cin >> d;

  std::cout << std::setprecision(2);
  std::cout << a << " ";
  std::cout << b << " ";
  std::cout << c << " ";
  std::cout << std::fixed << d << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
