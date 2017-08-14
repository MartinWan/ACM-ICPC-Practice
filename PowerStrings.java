import java.io.*;

// Solution to 'Power Strings' from Waterloo's 2002 Programming Contest
// https://open.kattis.com/problems/powerstrings
//
// Accepted in 0.76 seconds.
// This problem is roughly equivalent to finding the shortest
// period in a string s. If we find the 2nd match of s in s + s,
// it satisfies the definition of a period, this can be done in
// linear time using KMP.

class PowerStrings {
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

  public static int match(String T, String P) {
    int n = T.length();
    int m = P.length();
    int[] pi = computePrefixFunction(P);
    int q = 0; // number of matched characters

    for (int i = 0; i < n; i++) {
      while (q > 0 && P.charAt(q) != T.charAt(i))
        q = pi[q-1];
      if (P.charAt(q) == T.charAt(i))
        q++;
      if (q == m)
        return i - m + 1;
    }

    return -1; // not found
  }

  public static void main(String[] args) throws IOException{
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    while (true) {
      String P = in.readLine();
      if (P.equals(".")) break;

      String T = (P+P).substring(1);
      int n = T.length();
      int m = P.length();

      System.out.println(m/(match(T, P)+1));
    }
  }
}
