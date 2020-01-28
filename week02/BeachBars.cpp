#undef NDEBUG

#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <map>
#include <tuple>
#include <algorithm>

typedef std::vector<int> VI;
typedef std::vector<long> VL;
typedef std::vector<VI> VVI;
typedef std::pair<int, int> TII;
typedef std::vector<TII> VT;

VL coord; // word positions
TII pointers; // store pointers
VL curCoord;


void testcase() {

  // Read input and do setup
  long n; std::cin >> n;
  coord = VL(n);


  for (int i = 0; i < n; ++i)
    std::cin >> coord[i];
  std::sort(coord.begin(), coord.end());

  /*
  // print coordinates
  for (int i = 0; i < n; ++i) {
    std::cout << coord[i];
  }
  std::cout << std::endl;
  */

  pointers = std::make_pair(0, 0);

  // Start Sliding Window algorithm
  VL result = VL();
  long maxParas = 0;
  long curParas = 1;
  long curMaxDist = std::numeric_limits<long>::max();
  long curDist;

  while (pointers.first < n) {

    while (pointers.second < (n - 1) && (coord[pointers.second + 1] - coord[pointers.first]) <= 200) {
      ++pointers.second;
      //std::cout << "right pointer: " << pointers.second << std::endl;
      ++curParas;

      if (curParas > maxParas) {
        // If reach new max of parasols delete current results.
        maxParas = curParas;
        result.clear();
        curMaxDist = std::numeric_limits<long>::max();
      }
      if (curParas >= maxParas) {
        // Calculate max distance and coordinates
        // Case only one solution if %2 == 0
        if ((coord[pointers.second] - coord[pointers.first]) % 2 == 0) {
          curDist = (coord[pointers.second] - coord[pointers.first]) / 2;
          if(curDist <= curMaxDist) {
            if ( curDist < curMaxDist) {
              curMaxDist = curDist;
              //std::cout << "curDist: " << curDist << " , " << pointers.first << pointers.second << std::endl;
              result.clear();
            }
            result.push_back(coord[pointers.first] + curDist);
            //std::cout << "put to result: " << pointers.first + curDist << std::endl;
          }

        }
        //Case two solutions if %2 == 1;
        else {
          curDist = (coord[pointers.second] - coord[pointers.first]) / 2 + 1;

          if(curDist <= curMaxDist) {
            if (curDist < curMaxDist) {
              curMaxDist = curDist;
              //std::cout << "curDist: " << curDist << " , " << pointers.first << pointers.second << std::endl;
              result.clear();
            }
            result.push_back(coord[pointers.second] - curDist);
            //std::cout << "put to result: " << pointers.first + curDist << std::endl;
            //std::cout << "put to result: " << pointers.second - curDist << std::endl;
            result.push_back(coord[pointers.first] + curDist);
          }
        }
      }
    }

    // Adjust left pointer
    ++pointers.first;
    //std::cout << "left pointer: " << pointers.first << std::endl;
    --curParas;
  }


  // output result
  std::cout << maxParas << " " << curMaxDist << std::endl;
  for (auto elem : result) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
