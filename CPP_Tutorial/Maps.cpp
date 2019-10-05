#include <iostream> // We will use C++ input/output via streams
#include <map>
#include <set>

void testcase() {

  int q; std::cin >> q;

  std::multimap<std::string, int> m;
  int a; std::string b;
  for(int i = 0; i < q; ++i) {
    std::cin >> a >> b;

    if(a == 0) {
      m.erase(b);
    }
    else {
      m.insert(std::make_pair(b, a));
    }
  }

  std::string key; std::cin >> key;

  if(m.empty()){
    std::cout << "Empty";
  }
  else{
    if(m.find(key) != m.end()) {

      auto range = m.equal_range(key);
      std::set<int> s;
      for(auto elem = range.first; elem != range.second; ++elem) {
          s.insert(elem -> second);
      }
      for(auto item : s) {
        std::cout << item << " ";
      }

    }
    else {
      std::cout << "Empty";
    }
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
