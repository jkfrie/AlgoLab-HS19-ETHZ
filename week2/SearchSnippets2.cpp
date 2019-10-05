#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>
#include <utility>

typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
typedef std::vector<std::pair<int, int>> VP;

VP allWords; // Vector of tuples sorted for word index
VI sequenceMemory; // Remembers which words and their count are in current interval
VI nrWords; // Number of each word

void testcase() {

  // Read input and do setup
  int n; std::cin >> n;

  nrWords = VI(n);
  allWords = VP();

  for (int i = 0; i < n; ++i)
    std::cin >> nrWords[i];

  int tmp;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < nrWords[i]; ++j) {
      std::cin >> tmp;
      allWords.push_back(std::make_pair(tmp, i));
    }
  }

  // Sort allWords according to increasing index
  std::sort(allWords.begin(), allWords.end());

  // Start Sliding Window Algorithm
  sequenceMemory = VI(n,0);
  int bestL = 0;
  int bestR = std::numeric_limits<int>::max();
  int curL;
  int curR;
  int pointerR = 0;
  int pointerL = 0;
  int curWords = 0;
  bool COMPLETE = false;

  for(int i = 0; i < allWords.size(); ++i) {
    pointerR = i;

    if(sequenceMemory[allWords[pointerR].second] == 0) {
      ++curWords;
      //std::cout << "curWords: " << curWords << std::endl;
      if (curWords == n) {
        //std::cout << "is complete" << std::endl;
        COMPLETE = true;
      }
    }

    // Add newly found word to SequenceMemory
    ++sequenceMemory[allWords[pointerR].second];
    //std::cout << "sequenceMemory: " << sequenceMemory[allWords[pointerR].second] << std::endl;

    // Move left pointer right if sequence is still complete
    while(sequenceMemory[allWords[pointerL].second] > 1){
      --sequenceMemory[allWords[pointerL].second];
      ++pointerL;
    }

    // Set CurR and curL
    curR = allWords[pointerR].first;
    //std::cout << "curR: " << curR << std::endl;
    curL = allWords[pointerL].first;
    //std::cout << "curL: " << curL << std::endl;

    // Check if we have a better interval
    //std::cout << "bestL: " << bestL << " bestR: " << bestR << std::endl;
    //std::cout << "curL: " << curL << " curR: " << curR << std::endl;
    if(COMPLETE && (curR - curL + 1) < (bestR - bestL + 1)) {
      bestL = curL;
      bestR = curR;
    }
  }
  std::cout << bestR - bestL + 1 << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t; std::cin >> t;
  for (int i = 0; i < t; ++i) {
    testcase();
  }
}
