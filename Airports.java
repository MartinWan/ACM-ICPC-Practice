import java.io.*;
import java.util.*;


class Flight {
  public int time;
  public int start;
  public int end;
  public Flight(int time, int start, int end) {
    this.time = time;
    this.start = start;
    this.end = end;
  }
}


public class Airports {
  static int N_MAX = 500;
  static int M_MAX = 500;
  static int[] inspection = new int[N_MAX];
  static int[][] dist = new int[N_MAX][N_MAX]; 
  static int[][] minDist = new int[N_MAX][N_MAX]; 
  static ArrayList<Flight> flights = new ArrayList<>();

  static boolean augmentingPath(int[][] Gf, int s, int t, int[] parent) {
    // standard BFS starting at s on Gf, storing parent of vertices in parent array

    int V = Gf.length;

    boolean[] visited = new boolean[V];
    Arrays.fill(visited, false);

    Queue<Integer> Q = new LinkedList<>();
    Q.add(s);
    visited[s] = true;

    while (!Q.isEmpty()) {
      int u = Q.poll();

      for (int v = 0; v < V; v++) {
        if (Gf[u][v] > 0 && !visited[v]) {
          Q.add(v);
          parent[v] = u;
          visited[v] = true;
        }
      }
    }

    return visited[t];
  }
  
  static int edmondsKarp(int[][] Gf, int source, int sink) {
    int V = Gf.length;
    int[] parent = new int[V];
    
    int maxflow = 0;

    while (augmentingPath(Gf, source, sink, parent)) {
      long pathflow = Integer.MAX_VALUE;
      int s = sink;

      // find augmenting path's bottleneck
      while (s != source) {
        pathflow = Math.min(pathflow, Gf[parent[s]][s]);
        s = parent[s];
      }
      
      maxflow += pathflow;

      // update residual capacities in Gf along augmenting path
      int v = sink;
      while (v != source) {
        Gf[parent[v]][v] -= pathflow;
        Gf[v][parent[v]] += pathflow;
        v = parent[v];
      }
    }
    
    return maxflow;
  }

  static void solveCase(int n, int m) {
    // Floyd-Warshall to find shortest time between airports
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          minDist[i][j] = Math.min(minDist[i][j], minDist[i][k] + minDist[k][j]);
        }
      }
    }

    // use flow network to solve maximum path-cover problem
    // on flight-connection graph
    int V = 2*m+2;
    int[][] flowNetwork = new int[V][V];
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        if (i == j) continue;

        // see if a plane can connect f1->f2
        Flight f1 = flights.get(i);
        Flight f2 = flights.get(j);

        if (f1.end != f2.start && f1.time + dist[f1.start][f1.end] + minDist[f1.end][f2.start] <= f2.time) 
          flowNetwork[i][m+j] = 1;

        if (f1.end == f2.start && f1.time + dist[f1.start][f1.end] <= f2.time)
          flowNetwork[i][m+j] = 1;
      }
    }

    int s = 2*m;
    int t = 2*m+1;
    for (int i = 0; i < m; i++) {
      flowNetwork[s][i] = 1;
      flowNetwork[m+i][t] = 1;
    }

    System.out.println(m-edmondsKarp(flowNetwork, s, t));
  }

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    String[] nm = in.readLine().split(" ");
    int n = Integer.parseInt(nm[0]);
    int m = Integer.parseInt(nm[1]);

    String[] inspectionTimes = in.readLine().split(" ");
    for (int i = 0; i < n; i++) {
      inspection[i] = Integer.parseInt(inspectionTimes[i]);
    }

    for (int i = 0; i < n; i++) {
      String[] travelTimes = in.readLine().split(" ");
      for (int j = 0; j < n; j++) {
        dist[i][j] = Integer.parseInt(travelTimes[j]) + inspection[j];
        minDist[i][j] = dist[i][j];
      }
    }

    for (int i = 0; i < m; i++) {
      String[] flightInfo = in.readLine().split(" ");
      flights.add(new Flight(Integer.parseInt(flightInfo[2]), Integer.parseInt(flightInfo[0])-1, Integer.parseInt(flightInfo[1])-1));
    }

    solveCase(n, m);
  }
}
