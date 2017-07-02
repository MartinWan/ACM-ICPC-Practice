import java.util.Scanner;
import java.util.HashMap;


// https://open.kattis.com/problems/compositions

class Compositions {
	private static HashMap<Integer, Integer> memo;
	private static int compositions(int n, int m, int k) {
		if (!memo.containsKey(n)) {
			int result;
			if (n == 0) {
				result = 1;
			} else {
				int sum = 0;
				for (int i = 1; i <= n; i++) {
					if (i % k != m) {
						sum += compositions(n-i, m, k);
					}
				}
				result = sum;
			}
			memo.put(n, result);
		}

		return memo.get(n);
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int K = in.nextInt();

		for (int i = 0; i < K; i++) {
			int dataSetNumber = in.nextInt();
			int n = in.nextInt();
			int m = in.nextInt();
			int k = in.nextInt();

			memo = new HashMap<>();
			System.out.printf("%d %d\n", dataSetNumber, compositions(n, m, k));
		}
	}
}
