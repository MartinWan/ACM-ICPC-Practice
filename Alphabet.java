import java.util.*;

// http://acmicpc-pacnw.org/ProblemSet/2016/div1.pdf Problem A

class Alphabet {
  private static String W = "abcdefghijklmnopqrstuvwxyz";

  private static int lcs(String X, String Y) {
    int m = X.length();
    int n = Y.length();
    int[][] c = new int[m+1][n+1];

    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        if (X.charAt(i-1) == Y.charAt(j-1))
          c[i][j] = c[i-1][j-1] + 1;
        else if (c[i-1][j] >= c[i][j-1]) 
          c[i][j] = c[i-1][j];
        else
          c[i][j] = c[i][j-1];
      }
    }

    return c[m][n];
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    System.out.println(W.length() - lcs(in.next(), W));
  }
}
