import java.util.*;

// https://open.kattis.com/problems/rationalsequence2

class ARationalSequence2 {
  private static int FInverse(int p, int q) {
    int result = 0;
    int bit = 0;

    while (p != 1 || q != 1) {
      if (q > p) {
        q -= p;
      } else {
        result |= 1 << bit;
        p -= q;
      }
      bit++;
    }

    result |= 1 << bit;

    return result;
  }
  
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int P = in.nextInt();

    for (int i = 0; i < P; i++) {
      int K = in.nextInt();
      String[] pq = in.next().split("/");
      int p = Integer.parseInt(pq[0]);
      int q = Integer.parseInt(pq[1]);
      System.out.printf("%d %d\n", K, FInverse(p, q));
    }
  }
}
