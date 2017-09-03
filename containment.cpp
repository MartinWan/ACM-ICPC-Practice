#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

int node(int x, int y, int z) {
  return z*100 + y*10 + x;
}

bool augmenting_path(vector<vector<int>>& Gf, int s, int t, vector<int>& parent) {
  // standard BFS starting at s on Gf, storing parent vertices in parent vector
  int V = Gf.size();

  vector<bool> visited(V);
  queue<int> Q;
  Q.push(s);
  visited[s] = true;

  while (!Q.empty()) {
    int u = Q.front(); 
    Q.pop();

    for (int v = 0; v < V; v++) {
      if (Gf[u][v] > 0 && !visited[v]) {
        Q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return visited[t];
}

int edmonds_karp(vector<vector<int>>& Gf, int source, int sink) {
  int V = Gf.size();
  vector<int> parent(V);

  int maxflow = 0;

  while (augmenting_path(Gf, source, sink, parent)) {
    long long pathflow = INT_MAX;
    int s = sink;

    // find augmenting path's bottleneck
    while (s != source) {
      pathflow = min(pathflow, (long long) Gf[parent[s]][s]);
      s = parent[s];
    }

    maxflow += pathflow;

    // update residual capacities along augmenting path
    int v = sink;
    while (v != source) {
      Gf[parent[v]][v] -= pathflow;
      Gf[v][parent[v]] += pathflow;
      v = parent[v];
    }
  }

  return maxflow;
}

// adds edge (node1, node2) and (node2, node1) to Gf
void join2(vector<vector<int>>& Gf, int node1, int node2) {
  Gf[node1][node2] += 1;
  Gf[node2][node1] += 1;
}

int main() {
  int n;
  cin >> n;
  
  vector<vector<int>> Gf(1002, vector<int>(1002));
  int source = 1000;
  int sink = 1001;
  
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      // link source to sides of lattice
      Gf[source][node(i, j, 0)] += 1;
      Gf[source][node(i, j, 9)] += 1;
      Gf[source][node(i, 0, j)] += 1;
      Gf[source][node(i, 9, j)] += 1;
      Gf[source][node(0, i, j)] += 1;
      Gf[source][node(9, i, j)] += 1;

      // connect each cube to neighbors
      for (int k = 0; k < 9; k++) {
        join2(Gf, node(i,j,k), node(i,j,k+1));
        join2(Gf, node(i,k,j), node(i,k+1,j));
        join2(Gf, node(k,i,j), node(k+1,i,j));
      }
    }
  }
 
  for (int i = 0; i < n; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    Gf[node(x,y,z)][sink] += 6;
  }

  cout << edmonds_karp(Gf, source, sink) << endl;
}
