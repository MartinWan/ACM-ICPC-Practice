import java.util.*;

// https://open.kattis.com/problems/ada

class Ada {
	private static int n;
	private static int[][] fprime = new int[10][11];

	private static boolean constant(int[] f, int fsize) {
		int C = f[0];
		for (int i = 0; i < fsize; i++) {
			if (f[i] != C)
				return false;
		}
		return true;
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		n = in.nextInt();

		for (int i = 0; i < n; i++) 
			fprime[0][i] = in.nextInt();

		int i = 0;
		while (!constant(fprime[i], n - i)) {
			for (int j = 0; j < n - i - 1; j++) {
				fprime[i+1][j] = fprime[i][j+1] - fprime[i][j];
			}
			i++;
		}
		// fprime[i] is constant 
		
		int degree = i;
		fprime[i][n-i] = fprime[i][0]; // extend function by 1 more value
		i--;
		while (i >= 0) {
			int iLength = n - i;
			fprime[i][iLength] = fprime[i][iLength-1] + fprime[i+1][iLength-1];
			i--;
		}

		System.out.printf("%d %d\n", degree, fprime[0][n]);
	}
}
