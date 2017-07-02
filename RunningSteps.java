import java.util.Scanner;
import java.math.BigInteger;

class RunningSteps {
	private static long binomialCoefficient(long N, long K) {
		double result = 1.0;
		
		for (long i = 1; i <= K; i++) {
			result *= N-i+1;
			result /= i;
		}

		return (long) result;
	}

	private static long ways(long s) {
		if (s % 2 != 0) {
			return 0;
		}
		
		long twoStrides = (s + 2) / 3;
		if (twoStrides % 2 != 0) {
			twoStrides++;
		}
		
		long count = 0;
		long k = twoStrides;

		while (2*k <= s) {
			long steps = s - k;
			long temp = binomialCoefficient(steps/2, k/2);
			count += temp * temp;
			k += 2;
		}

		return count;
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		long K = scanner.nextInt();
		
		for (long i = 0; i < K; i++) {
			long k = scanner.nextInt();
			long S = scanner.nextInt();
			System.out.printf("%d %d\n", k, ways(S));
		}
	}
}
