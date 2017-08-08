#include <stdio.h>
#define GRID_LENGTH 100
#define GRID_AREA 10000


// Solution to "Forest Fires" from Baylor's Competitive Learning Course
// Accepted in 0.28 seconds
//
// https://open.kattis.com/problems/forestfires
//
// Explanation:
// Fire can only spread from tree a to b if they are connected.
// So this problem is a simple application of union find.


int r, n;
bool is_tree[GRID_LENGTH][GRID_LENGTH];

class DisjointSets {
  private:
    int N;
    int* id;
    int* sizes;
  public:
    DisjointSets(int N) {
      this->N = N;
      sizes = new int[N];
      id = new int[N];
      for (int i = 0; i < N; i++) {
        sizes[i] = 1;
        id[i] = i;
      }
    }

    ~DisjointSets() {
      delete[] id;
      delete[] sizes;
    }

    bool connected(int v1, int v2) {
      return find(v1) == find(v2);
    }

    int find(int v) {
      int p = id[v];
      while (p != id[p]) {
        id[p] = id[id[p]];
        p = id[p];
      }
      return p;
    }

    void join(int v1, int v2) {
      if (v1 < 0 || v1 >= N)
        return;
      if (v2 < 0 || v2 >= N)
        return;

      int i = find(v1);
      int j = find(v2);
      
      if (i != j) {
        if (sizes[i] < sizes[j]) {
          id[i] = id[j];
          sizes[j] += sizes[i];
        } else {
          id[j] = id[i];
          sizes[i] += sizes[j];
        }
      }
    }
};

int next_r() {
  r = (r*5171 + 13297) % 50021;
  return r;
}


void solve_case() {
  DisjointSets S(GRID_AREA);
 
  // clear is_tree  
  for (int i = 0; i < GRID_LENGTH; i++) 
    for (int j = 0; j < GRID_LENGTH; j++) 
        is_tree[i][j] = false;
 
  int t[n];
  int report = 0;
  
  for (int i = 0; i < n; i++) {
    // choose tree
    int m = next_r() % GRID_AREA;
    int y = m % GRID_LENGTH;
    int x = m/GRID_LENGTH;
    while (is_tree[x][y]) {
      m = next_r() % GRID_AREA;
      y = m % GRID_LENGTH;
      x = m/GRID_LENGTH;
    }
    t[i] = m;

    // place tree on is_tree
    is_tree[x][y] = true;

    // union tree with neighbor trees
    if (x+1 < GRID_LENGTH && is_tree[x+1][y]) 
      S.join(m, GRID_LENGTH*(x+1) + y);
    if (x-1 >= 0 && is_tree[x-1][y]) 
      S.join(m, GRID_LENGTH*(x-1) + y);
    if (y+1 < GRID_LENGTH  && is_tree[x][y+1]) 
      S.join(m, GRID_LENGTH*x + y+1);
    if (y-1 >= 0 && is_tree[x][y-1]) 
      S.join(m, GRID_LENGTH*x + y-1);
 
    // see if fire can spread from a -> b
    int a = next_r() % (i+1);
    int b = next_r() % (i+1);

    if (S.connected(t[a], t[b])) 
      report++;

    // output every 100 iterations
    if ((i+1) % 100 == 0) {
      printf("%d ", report);
      report = 0;
    }
  }

  printf("\n");
}

int main() {  
  while (scanf("%d %d\n", &r, &n) != EOF) {
   solve_case();
  }
}

