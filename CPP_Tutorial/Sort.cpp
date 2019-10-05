#include <iostream> // We will use C++ input/output via streams
#include <vector>
#include <algorithm>

void testcase() {

  // read input
  int n; std::cin >> n;
  std::vector<int> numbers(n, 0);
  int tmp;
  for(int i = 0; i < n; ++i){
    std::cin >> tmp;
    numbers[i] = tmp;
  }
  int x; std::cin >> x;

  //sort increasing
  if(x == 0) {
      std::sort(numbers.begin(), numbers.end());
  }

  //sort decreasing
  else {
      std::sort(numbers.begin(), numbers.end(), std::greater<int>());
  }

  for(auto elem : numbers) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
