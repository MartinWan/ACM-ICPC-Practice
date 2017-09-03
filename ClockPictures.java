import java.util.*;
import java.io.*;
import java.util.stream.*;

class KMP {

  // Returns an array pi[] such that
  // pi[q] = "length of longest prefix that is a proper suffix of P[0...q]"
  // That is, pi[q] = max { k < q : P[0...k] is a suffix of P[0...q] }
  static int[] computePrefixFunction(String P) {
    int m = P.length();
    int[] pi = new int[m];
    pi[0] = 0;
    int k = 0;

    for (int q = 1; q < m; q++) {
      while (k > 0 && P.charAt(k) != P.charAt(q))
        k = pi[k-1];
      if (P.charAt(k) == P.charAt(q))
        k++;
      pi[q] = k;
    }
    
    return pi;
  }
 
  // returns index i such that
  // P occurs in T starting at index i
  // returns -1 if no such index exists
  // Time Complexity: O(|T| + |P|)
  public static int match(String T, String P) {
    int n = T.length();
    int m = P.length();
    int[] pi = computePrefixFunction(P);
    int matches = 0;

    for (int i = 0; i < n; i++) {
      while (matches > 0 && P.charAt(matches) != T.charAt(i))
        matches = pi[matches-1];
      if (P.charAt(matches) == T.charAt(i))
        matches++;
      if (matches == m)
        return i - m + 1;
    }

    return -1; // not found
  }

  public static void main(String[] args) {
    System.out.println(match("bcabc", "abc"));    
  }
}


public class ClockPictures {
  static int N_MAX = 200000;
  static int[] ticks1 = new int[N_MAX];
  static int[] ticks2 = new int[N_MAX];
  static int[] intervals1 = new int[N_MAX];
  static int[] intervals2 = new int[N_MAX];

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    int n = Integer.parseInt(in.readLine());
    
    String[] t1 = in.readLine().split(" ");
    String[] t2 = in.readLine().split(" ");
    for (int i = 0; i < n; i++) {
      ticks1[i] = Integer.parseInt(t1[i]);
      ticks2[i] = Integer.parseInt(t2[i]);
    }
    Arrays.sort(ticks1, 0, n);
    Arrays.sort(ticks2, 0, n);

    for (int i = 0; i < n - 1; i++) {
      intervals1[i] = ticks1[i+1] - ticks1[i];
      intervals2[i] = ticks2[i+1] - ticks2[i];
    }
    intervals1[n-1] = ticks1[0] + 360000 - ticks1[n-1];
    intervals2[n-1] = ticks2[0] + 360000 - ticks2[n-1];

    String s1 = Arrays.stream(intervals1, 0, n)
      .mapToObj(String::valueOf)
      .collect(Collectors.joining(" "));

    String s2 = Arrays.stream(intervals2, 0, n)
      .mapToObj(String::valueOf)
      .collect(Collectors.joining(" "));
    
		if (KMP.match(s1+" "+s1, s2) == -1)
			System.out.println("impossible");
		else 
			System.out.println("possible");
  }
}
