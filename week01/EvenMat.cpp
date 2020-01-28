#include <vector>
#include <iostream>

typedef std::vector<int> VI;
typedef std::vector<VI> VII;

void testcase() {

  // read input and calculate sum of entire matrice
  int n; std::cin >> n;

  VII numbers(n, VI(n, 0));
  int tmp;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      std::cin >> tmp;
      numbers[i][j] = tmp;
    }
  }

  /*
  // print matrix
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      std::cout << numbers[i][j] << " ";
    }
    std::cout << std::endl;
  }
  */

  // calculate partSum matrix in following fashion partSum[i, j] = sum of all
  // in submatrix starting at (0,0) and ending at (i,j)
  VII partSums(n, VI(n,0));
  int curSum;

  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j) {
      if(i == 0) {
        if(j == 0) {
          partSums[0][0] = numbers[0][0];
        }
        else {
          partSums[0][j] = partSums[0][j - 1] + numbers[0][j];
        }
      }
      else {
        if(j == 0) {
          partSums[i][0] = partSums[i - 1][0] + numbers[i][j];
        }
        else {
          partSums[i][j] = partSums[i][j - 1] + partSums[i - 1][j] - partSums[i-1][j-1] + numbers[i][j];
        }
      }
    }
  }

  /*
  // print partSUms matrix
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      std::cout << partSums[i][j] << " ";
    }
    std::cout << std::endl;
  }
  */



  int counter = 0;
  int matSum = 0;
  for(int il = 0; il < n; ++il) {
    for(int iu = il; iu < n; ++iu) {
      for(int jl = 0; jl < n; ++jl) {
        for(int ju = jl; ju < n; ++ju) {
          matSum = 0;
          if(il != 0 && jl != 0) {
            matSum = partSums[iu][ju] - partSums[iu][jl - 1] - partSums[il - 1][ju] + partSums[il - 1][jl - 1];
            //std::cout << "matsum: " << matSum << " " << partSums[iu][jl - 1] << partSums[il - 1][ju] << std::endl;
            //std::cout << partSums[iu][ju] << partSums[il][jl] << std::endl;
          }
          else {
            if(il == 0 && jl == 0) {
              matSum = partSums[iu][ju];
            }
            else if(il == 0) {
              matSum = partSums[iu][ju] - partSums[iu][jl - 1];
            }
            else {
              matSum = partSums[iu][ju] - partSums[il - 1][ju];
            }
          }
          if(matSum % 2 == 0) {
            ++counter;
            //std::cout << "found: " << il << jl << ", " << iu << ju << std::endl;;
          }
        }
      }
    }
  }
  /*
  // calculate partialSums of each row (On²)
  VII partSums(n, VI(n, 0));
  long curSum;
  for(int i = 0; i < n; ++i) {
    curSum = 0;
    for (int j = 0; j < n * n; ++j) {
      curSum += numbers[i][j];
      partSums[i][j] = curSum;
      }
    }
  }

  // sum up the columns of partialSum matrix
  VI parSumOfCols(n, 0);
  for(int j = 0; j < n; ++j) {
    for(int i = 0; i < n; ++i) {
      parSumOfCols[j] += numbers[i][j];
    }
  }


  // fix left and right and calculate sum of all submatrices
  for(int j1 = 0; j1 < n; ++j1) {
    for(int j2 = i1; j2 < n; ++j2){
      for()
    }
  }
*/
  std::cout << counter << std::endl;
}


int main() {
  std::ios_base::sync_with_stdio(false); // Always!
  int t; std::cin >> t; // Read the number of test cases
  for (int i = 0; i < t; ++i)
    testcase(); // Solve a particular test case
}
