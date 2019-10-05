#include <iostream> // We will use C++ input/output via streams

std::string reverseString(std::string word) {
  int n = word.length();
  for (int i = 0; i < (n / 2); ++i) {
    char tmp = word[i];
    word[i] = word[n - 1 - i];
    word[n - 1 - i] = tmp;
  }
  return word;
}

void testcase() {

  std::string a; std::cin >> a;
  std::string b; std::cin >> b;

  std::cout << a.length() << " " << b.length() << std::endl;
  std::cout << a + b << std::endl;

  a = reverseString(a);
  b = reverseString(b);
  char tmp = a[0];
  a[0] = b[0];
  b[0] = tmp;

  std::cout << a << " " << b << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
