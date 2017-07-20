import java.util.*;

// http://acmicpc-pacnw.org/ProblemSet/2015/Statements/div1.pdf Problem E

class Excellence {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    int[] S = new int[n];

    for (int i = 0; i < n; i++)
      S[i] = in.nextInt();

    Arrays.sort(S);
    int m = n / 2;
    int min = Integer.MAX_VALUE;
    for (int i = 0; i < m; i++)
      min = Math.min(min, S[i] + S[n - 1 - i]);

    System.out.println(min);
  }
}
