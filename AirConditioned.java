import java.io.*;
import java.util.*;

class Interval implements Comparable<Interval> {
  public int start;
  public int end;
  public Interval(int s, int e) {
    start = s;
    end = e;
  }
 
  @Override
  public int compareTo(Interval other) {
    return Integer.compare(this.end,  other.end);
  }
}

class AirConditioned {
  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    int n = Integer.parseInt(in.readLine());
    Interval[] intervals = new Interval[n];

    for (int i = 0; i < n; i++) {
      String[] startEnd = in.readLine().split(" ");
      int start = Integer.parseInt(startEnd[0]);
      int end = Integer.parseInt(startEnd[1]);

      intervals[i] = new Interval(start, end);
    }

    Arrays.sort(intervals); // sort intervals by right

    int roomRight = 0;
    int count = 0;
    for (Interval interval: intervals) {
      if (interval.start > roomRight) { // fits in room
        roomRight = interval.end;
        count++;
      }  
    }

    System.out.println(count);
  }
}
