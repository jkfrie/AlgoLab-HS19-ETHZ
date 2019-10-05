#include <iostream> // We will use C++ input/output via streams
#include <vector>
#include <queue>

typedef std::vector<int> VI; // Stands for a vector of integers
typedef std::vector<VI> VVI; // Stands for a vector of vectors
typedef std::queue<int> QI;  // Stands for a queue of integers

void testcase() {

  int n; long m; int v; std::cin >> n >> m >>v;

  //in case Graph is empty abort
  if(n <= 0) {
    return;
  }

  //create adjacency list
  VVI adList(n, VI());
  int a; int b;
  for(long i = 0; i < m; ++i) {
    std::cin >> a >> b;
    adList[a].push_back(b);
    //adList[b].push_back(a);
  }

  //print adjacency List
  /*
  for(int i = 0; i < n; ++i){
    for(auto elem : adList[i]) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }
  /**/

  //create distance vector
  VI distances(n, -1);

  //create visited vector
  VI visited(n, 0);

  //create node queue and add first vertex
  QI q;
  q.push(v);

  //start DFS
  int distance = 0;
  int curNode;
  visited[curNode] = 1;
  distances[v] = 0;

  while(!q.empty()) {
    curNode = q.front();
    q.pop();
    distance = distances[curNode] + 1;

    //check if node on queue is already visited
    //if(visited[curNode] == 0) {

      //visited[curNode] = 1;

    //loop over all edges curNode has
    for(auto elem : adList[curNode]) {
      //std::cout << "looked at edge from " << curNode << " to " << elem << std::endl;

      //if has unvisited neighbours add to stack
      if(visited[elem] == 0) {
        q.push(elem);
        distances[elem] = distance;
        visited[elem] = 1;
          //std::cout << "["<< elem << "]" << std::endl;
      }
    }
  }

  //print Output
  for(auto elem : distances) {
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
