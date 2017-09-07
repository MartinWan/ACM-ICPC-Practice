import java.io.*;
import java.util.*;

class SeiveOfEratosthenes {
  /*
   * Returns a BitSet such that bit 0 <= i <= n is 1 iff
   * i is a prime number in O(nloglogn) time
   */
  public static BitSet apply(int n) {
    BitSet primes = new BitSet(n+1); // primes[i] = 1 iff i is a prime number

    primes.set(0, 2, false);
    primes.set(2, n+1, true);

    for (int i = 2; i*i <= n; i++) {
      if (primes.get(i)) {
        for (int j = i*i; j <= n; j += i) {
          primes.set(j, false);
        }
      }
    }

    return primes;
  }
}

class PrimeSeive {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    String[] nq = in.readLine().split(" ");
    int n = Integer.parseInt(nq[0]);
    int q = Integer.parseInt(nq[1]);

    BitSet primes = SeiveOfEratosthenes.apply(n);

    System.out.println(primes.cardinality());

    for (int i = 0; i < q; i++) {
      int x = Integer.parseInt(in.readLine());
      System.out.println(primes.get(x)? 1 : 0);
    }


  }
}
