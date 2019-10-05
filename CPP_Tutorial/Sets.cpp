#include <iostream> // We will use C++ input/output via streams
#include <set>

void testcase() {

  int q; std::cin >> q;

  std::set<int> s;
  int a; int b;
  for(int i = 0; i < q; ++i) {
    std::cin >> a >> b;

    if(a == 0) {
      s.insert(b);
    }
    else {
      auto it = s.find(b);
      if(it != s.end()) {
        s.erase(it);
      }
    }
  }

  if(s.empty()){
    std::cout << "Empty";
  }
  else{
    for(auto i : s){
      std::cout << i << " ";
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
