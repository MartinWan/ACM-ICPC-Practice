import java.io.*;
import java.util.*;


/**
  * Weighted quick union with path compression.
  * Unions N elements in O(Nlog*(N)) ~ O(N)
  * Where log*(N) is the inverse of the super exponential
  * e.g. 2^(2^(2^(2...)))
  */
class UnionFind {
  private int N;
  private int[] size;
  private int[] id;

  public UnionFind(int N) {
    this.N = N;
    this.size = new int[N];
    this.id = new int[N];

    for (int i = 0; i < N; i++) {
      this.size[i] = 1;
      this.id[i] = i;
    }
  }

  public boolean connected(int v1, int v2) {
    return find(v1) == find(v2);
  }

  public void union(int v1, int v2) {
    if (v1 < 0 || v1 >= N) return;
    if (v2 < 0 || v2 >= N) return;

    int i = find(v1);
    int j = find(v2);

    if (i != j) { // v1, v2 not already unioned
      // smaller tree always merged into larger tree to maintain balance
      if (size[i] < size[j]) {
        id[i] = id[j];
        size[j] += size[i];
      } else {
        id[j] = id[i];
        size[i] += size[j];
      }
    }
  }

  private int find(int v) {
    int p = id[v];
    while (p != id[p]) {
      id[p] = id[id[p]]; // path compression
      p = id[p];
    }
    return p;
  }
}


public class KindsOfPeople {
  static int[][] grid;
  static int r;
  static int c;
  static UnionFind D; // decimal connectivity
  static UnionFind B; // binary connectivity

  static int get(int i, int j) {
    if (i < 0 || i >= r) return -1;
    if (j < 0 || j >= c) return -1;

    return grid[i][j];
  }

  static void unionNeighbors(int i, int j) {
    int zone = i*c + j;
    int color = grid[i][j];
    UnionFind S = color == 1? D : B;
    
    if (get(i+1, j) == color) S.union(zone, (i+1)*c + j);
    if (get(i-1, j) == color) S.union(zone, (i-1)*c + j);
    if (get(i, j+1) == color) S.union(zone, i*c + j+1);
    if (get(i, j-1) == color) S.union(zone, i*c + j-1);
  }

  public static void main(String[] args) throws IOException{
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    String[] rc = in.readLine().split(" "); r = Integer.parseInt(rc[0]); c = Integer.parseInt(rc[1]);

		B = new UnionFind(r*c); // stores connectivity of binary
		D = new UnionFind(r*c); // stores connectivity of decimal

    grid = new int[r][c];
 
    // init grid
		for (int i = 0; i < r; i++) {
      String line = in.readLine();
      for (int j = 0; j < c; j++) {
        grid[i][j] = line.charAt(j) == '0'? 0 : 1;
      }
    }
	
    // union all neighbors on grid
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        unionNeighbors(i, j);     
      }
    }

    int n = Integer.parseInt(in.readLine()); 

    for (int i = 0; i < n; i++) {
      String[] r1c1r2c2 = in.readLine().split(" ");
      int r1 = Integer.parseInt(r1c1r2c2[0]) - 1;
      int c1 = Integer.parseInt(r1c1r2c2[1]) - 1;
      int r2 = Integer.parseInt(r1c1r2c2[2]) - 1;
      int c2 = Integer.parseInt(r1c1r2c2[3]) - 1;
    
      int X = r1*c + c1;
      int Y = r2*c + c2;
            
      if (D.connected(X, Y)) System.out.println("decimal");
      else if (B.connected(X, Y)) System.out.println("binary");
      else System.out.println("neither");
    }
  }
}
