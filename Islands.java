import java.util.*;

class Islands {
  static int MAX_SIZE = 12;
  static int P;
  static int[] seq = new int[MAX_SIZE];
  
  private static boolean isIsland(int i, int j) {
    int L = seq[i-1];
    int R = seq[j+1];

    for (int k = i; k <= j; k++) {
      if (seq[k] <= L || seq[k] <= R) 
        return false;
    }

    return true;
  }

  private static int islands() {
    int count = 0;
    for (int s = 1; s <= 10; s++) {
      for (int i = 1; i <= 10 - s + 1; i++) {
        if (isIsland(i, i+s-1))
          count++;
      }
    }
    return count;
  }
  
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    P = in.nextInt();

    for (int i = 0; i < P; i++) {
      int K = in.nextInt();
      
      for (int j = 0; j < MAX_SIZE; j++)
        seq[j] = in.nextInt();

      System.out.printf("%d %d\n", K, islands());
    }
  }
}
