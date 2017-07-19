import java.util.*;
import java.math.BigInteger;

// https://open.kattis.com/problems/rats

class RATS {
  private static String getNext(String digits) {
    String reversed = new StringBuffer(digits).reverse().toString();
    
    String next = (new BigInteger(digits).add(new BigInteger(reversed))).toString();
    char[] temp = next.toCharArray();

    Arrays.sort(temp);
    BigInteger result = new BigInteger(new String(temp));

    while (result.mod(BigInteger.TEN).equals(BigInteger.ZERO))
      result = result.divide(BigInteger.TEN);

    return result.toString();
  }

  private static void solveCase(int K, int M, String current) {
    Set<String> visited = new HashSet<>();
    
    for (int i = 1; i < M; i++) {
      if (current.matches("1233+4444") || current.matches("5566+7777")) {
        System.out.printf("%d %c %d\n", K, 'C', i);
        return;
      }

      if (visited.contains(current)) {
        System.out.printf("%d %c %d\n", K, 'R', i);
        return;
      }

      visited.add(current);

      current = getNext(current);
    }

    if (visited.contains(current)) {
      System.out.printf("%d %c %d\n", K, 'R', M);
      return;
    }

    System.out.printf("%d %s\n", K, current);
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int P = in.nextInt();

    for (int i = 0; i < P; i++) {
      int K = in.nextInt();
      int M = in.nextInt();
      String start = in.next();
      solveCase(K, M, start);
    }
  }
}
