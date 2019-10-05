#include <vector>
#include <iostream>

typedef std::vector<int> VI;
typedef std::vector<long> VL;

long long fac(long long n) {
  if(n <= 1) {
    return 1;
  }
  else {
    return n * fac(n - 1);
  }
}

void testcase() {

  // read input
  int n; std::cin >> n;

  VI numbers(n);
  int tmp;
  for(int i = 0; i < n; ++i) {
    std::cin >> tmp;
    numbers[i] = tmp;
  }

  //count even and odd partial sums
  int even = 0;
  int odd = 0;
  int curSum = 0;
  for (int i = 0; i < n; ++i) {
    curSum += numbers[i];
    if(curSum % 2 == 0) {
      ++even;
    }
  }
  odd = n - even;

  // calculate result
  std::cout << "even: " << even << ", " << "odd: " << odd << ", " << std::endl;
  std::cout << fac(even - 2) << "  " << fac(odd - 2) << std::endl;
  std::cout << fac(even) << "  " << fac(odd) << std::endl;
  //result = fac(even) / (2 * fac(even - 2));
  //result += fac(odd) / (2 * fac(odd - 2));
  long result = (odd * (odd - 1)) / 2;
  result += (even * (even - 1)) / 2;
  result += even;

  // output result
  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
