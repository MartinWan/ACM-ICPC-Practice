import java.util.*;


// https://open.kattis.com/problems/apples

class FallingApples {
  private static int N_MAX = 50000;
  private static int M_MAX = 10;
  private static int n;
  private static int m;
  private static char[][] grid = new char[N_MAX][M_MAX];

  private static void putApples(int apples, int obstacle, int j) {
    for (int i = 1; i <= apples; i++) {
      grid[obstacle-i][j] = 'a';
    }
  }

  private static void simulateColumn(int j) {
    int obstacle = n;

    while (obstacle >= 0) {
      int i = obstacle - 1;
      int apples = 0;

      while (i >= 0 && grid[i][j] != '#') {
        if (grid[i][j] == 'a') {
          apples++;
          grid[i][j] = '.';
        }
        i--;
      }
      putApples(apples, obstacle, j);
  
      obstacle = i;
    }

  }

  private static void dropApples() {
    for (int j = 0; j < m; j++) {
      simulateColumn(j);
    }
  }

  private static void printGrid() {
    for (int i = 0; i < n; i++) 
      System.out.println(new String(grid[i]));
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    n = in.nextInt();
    m = in.nextInt();

    for (int i = 0; i < n; i++) {
      String line = in.next();
      for (int j = 0; j < m; j++) {
        grid[i][j] = line.charAt(j);
      }
    }
    
   dropApples(); 
   printGrid();
  }
}
