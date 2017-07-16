import java.util.*;

// https://open.kattis.com/problems/mancala

class Mancala {
  static int P;
  static int MAX_B = 80;
  static int[] bins = new int[MAX_B+1];

  public static void main(String[] argrs) {
    Scanner in = new Scanner(System.in);

    P = in.nextInt();
    for (int i = 0; i < P; i++) {
      int K = in.nextInt();
      int N = in.nextInt();
      Arrays.fill(bins, 0);

      // find winning states up to N
      for (int j = 0; j < N; j++) {
        int k = 1;
        while (bins[k] != 0) { // input guarantees never to exceed MAX_B
          k++;
        }
        bins[k] = k;

        k--;
        while (k >= 0) {
          bins[k]--;
          k--;
        }
      }

      // output solution
      int k = MAX_B;
      while (bins[k] == 0) {
        k--;
      }

      System.out.printf("%d %d\n", K, k);
      for (int j = 1; j <= k; j++) {
        System.out.printf("%d ", bins[j]);
        if (j % 10 == 0) 
          System.out.printf("\n");
      }

      System.out.printf("\n");
    }
  }
}
