import java.util.*;

// Solution to Problem H from the ACM ICPC Pacific NW 2016
//
// http://acmicpc-pacnw.org/ProblemSet/2016/div1.pdf
//
// Explanation:
// Considering each interval sorted by their right endpoint,
// To maximize the fence we can paint, we can either include the interval and discard its conflicts, 
// or not include the interval. This leads to a dynamic programming solution
// Where dp[k] = max fencing we can paint up to and including interval k in the sorted order
// dp[k+1] = max { k+1'th interval size + dp[first interval to left of k+1], dp[k] }

class Interval implements Comparable<Interval>  {
  public long left;
  public long right;
  public Interval(long l, long r) {
    this.left = l;
    this.right = r;
  }

  public int compareTo(Interval that) {
    return Long.compare(this.right, that.right);
  }

  public long size() {
    return right - left + 1;
  }
}


class Paint {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    long n = in.nextLong();
    long k = in.nextLong();

    Interval[] intervals = new Interval[(int) k];
    for (int i = 0; i < k; i++) {
      intervals[i] = new Interval(in.nextLong(), in.nextLong());
    }

    Arrays.sort(intervals);

    long best = Integer.MIN_VALUE;

    TreeMap<Long, Long> dp = new TreeMap<>();
    for (Interval I : intervals) {
      Long left = dp.lowerKey(I.left);
      long leftValue = (left == null) ? 0 : dp.get(left);
      
      best = Math.max(best, leftValue + I.size());
      dp.put(I.right, best);
    }
    
    System.out.println(n-best);
  }
}
