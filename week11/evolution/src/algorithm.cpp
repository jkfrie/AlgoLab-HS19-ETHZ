#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <map>
#include <utility>
#include <stdexcept>
#include <string>

using namespace std;

#define REP(i, n) for(int i = 0; i < n; ++i)

vector<vector<int>> tree;
vector<int> ages;
map<string, int> species_to_index;
vector<string> species;

string binary_search(vector<int> &path, int x) {

  int l = -1;
  int r = path.size() - 1;

  while(l + 1 < r) {
    int m = (l + r) / 2;
    if(ages[path[m]] <= x) r = m;
    else l = m;
  }
  return species[path[r]];
}

void dfs(int node, vector<int> &path, vector<string> &results, vector<vector<pair<int, int>>> &queries) {

  // loop over all queries for current node and find result with binary_search
  for(auto query : queries[node]) {
    results[query.first] = binary_search(path, query.second);
  }

  // loop over all sons and perform dfs
  for(auto son : tree[node]) {
    path.push_back(son);
    dfs(son, path, results, queries);
  }

  // maintain path invariant
  path.pop_back();
}

void testcase() {
  // Read input
  int n, q; cin >> n >> q;

  species = vector<string>(n);
  ages = vector<int>(n);
  REP(i, n) {
    string name; cin >> name;
    int age; cin >> age;
    species_to_index[name] = i;
    species[i] = name;
    ages[i] = age;
  }

  tree = vector<vector<int>>(n);
  REP(i, n - 1) {
    string s, p; cin >> s >> p;
    tree[species_to_index[p]].push_back(species_to_index[s]);
  }

  // store queries directly at nodes
  vector<vector<pair<int, int>>> queries(n);
  REP(i, q) {
    string s; cin >> s;
    int b; cin >> b;
    queries[species_to_index[s]].push_back(make_pair(i, b));
  }

  // find root node
  int root = max_element(ages.begin(), ages.end()) - ages.begin();

  // Perform DFS on tree and directly solve all queries at the nodes with binary search
  vector<string> results(q);
  vector<int> path;
  path.push_back(root);
  dfs(root, path, results, queries);

  // output result
  for(int i = 0; i < q; ++i) {
    cout << results[i];
    if(i < q - 1) cout << " ";
  }
  cout << endl;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) testcase();
}
