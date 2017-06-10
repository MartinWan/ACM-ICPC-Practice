#include <iostream>
using namespace std;

// problem: https://open.kattis.com/problems/wheresmyinternet

class DisjointSets {
  private:
    int N;
    int* id;
    int* sizes;
  public:
    DisjointSets(int N) {
      this->N = N;
      sizes = new int[N+1];
      id = new int[N+1];
      for (int i = 1; i <= N; i++) {
        sizes[i] = 1;
        id[i] = i;
      }
    }

    int find(int v) {
      int p = id[v];
      while (p != id[p]) {
        p = id[p];
      }
      return p;
    }

    void join(int v1, int v2) {
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

int main() {
  int M, N;
  cin >> N;
  cin >> M;
  
  DisjointSets* S = new DisjointSets(N);
  for (int i = 1; i <= M; i++) {
    int v1;
    int v2; 
    cin >> v1;
    cin >> v2;

    S->join(v1, v2);
  }

  int origin = S->find(1);
  int connected = true;
  for (int i = 1; i <= N; i++) {
    if (S->find(i) != origin) {
      connected = false;
      cout << i << endl;
    }
  }
  if (connected) {
    cout << "Connected" << endl; 
  }
}
