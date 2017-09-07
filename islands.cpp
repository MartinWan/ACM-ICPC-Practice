#include<iostream>
#include<vector> 
using namespace std;


/*
 * Problem T from ACM ICPC NW 2016 Div 2
 * http://acmicpc-pacnw.org/ProblemSet/2016/div2.pdf
 */

int n, m;

void visit(vector<string>& grid, int i, int j, vector<vector<bool>>& visited) {
  if (i < 0 || i > n - 1) return;
  if (j < 0 || j > m - 1) return;
  if (grid[i][j] == 'W') return;

  if (!visited[i][j]) {
    visited[i][j] = true;
    
    visit(grid, i+1, j, visited);
    visit(grid, i-1, j, visited);
    visit(grid, i, j+1, visited);
    visit(grid, i, j-1, visited);
  }
}

int connected_component_count(vector<string>& grid) {
  vector<vector<bool>> visited(n, vector<bool>(m));
  
  int count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!visited[i][j] && grid[i][j] == 'L') {
        count++;
        visit(grid, i, j, visited);
      }
    }
  }
  return count;
}

int main() {
  cin >> n >> m;

  vector<string> grid(n);
  for (int i = 0; i < n; i++) {
    cin >> grid[i];
  }

  cout << connected_component_count(grid) << endl;
}
