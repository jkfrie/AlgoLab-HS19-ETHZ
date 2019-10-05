#include <iostream> // We will use C++ input/output via streams
#include <vector>
#include <stack>

typedef std::vector<int> VI; // Stands for a vector of integers
typedef std::vector<VI> VVI; // Vector of vectors of integers, i.e. a 2D matrix
typedef std::stack<int> STI;  // Stands for a stack of integers

void testcase() {

  int n; long m; int v; std::cin >> n >> m >>v;

  //in case Graph is empty abort
  if(n <= 0) {
    return;
  }

  //create adjacency matrix
  VVI adMat(n, VI(n, 0));
  int a; int b;
  for(long i = 0; i < m; ++i) {
    std::cin >> a >> b;
    adMat[a][b] = 1;
    adMat[b][a] = 1;
  }

  /*
  //print adjacency matrix
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j) {
      std::cout << adMat[i][j] << " ";
    }
    std::cout << std::endl;
  }
  */

  //create timestamp vectors
  VI found(n, -1);
  VI finished(n, -1);

  //create visited vector
  VI visited(n, 0);

  //create node stack and add first vertex
  STI s;
  s.push(v);

  //start DFS
  int timer = 0;
  int curNode;
  bool hasNextNode;

  while(!s.empty()) {
    curNode = s.top();
    //s.pop();

    //check if node on stack is already visited
    if(visited[curNode] == 0) {

      hasNextNode = false;
      visited[curNode] = 1;
      found[curNode] = timer;
      ++timer;

      //loop over all edges curNode has
      for(int i = n - 1; i > 0; --i) {
        //std::cout << "looked at edge from " << curNode << " to " << i << std::endl;

        //if has unvisited neighbours add to stack
        if(adMat[curNode][i] == 1 && visited[i] == 0) {
          s.push(i);
          //std::cout << "["<< i << "]" << std::endl;
          hasNextNode = true;
        }
      }

      //if did not find any unvisited nodes -> start backtracking
      if(hasNextNode == false) {
        s.pop();
        finished[curNode] = timer;
        //std::cout << "finished: " << curNode << std::endl;
        ++timer;
      }
    }

    //if node on top of stack already visited get finish timer value
    else {
      s.pop();
      if(finished[curNode] == -1) {
        finished[curNode] = timer;
        ++timer;
      }
      //std::cout << "finished: " << curNode << std::endl;
    }

  }

  //print Output
  for(auto elem : found) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
  for(auto elem : finished) {
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
