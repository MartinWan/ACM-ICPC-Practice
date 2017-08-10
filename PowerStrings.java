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
  static char[] P;
	static char[] T;
	static int[] b;
	static int n, m;
  
	static void kmpPreprocess() { // call this before calling kmpSearch()
    b = new int[m+1];
		int i = 0, j = -1; b[0] = -1; // starting values
    while (i < m) { // pre-process the pattern string P
      while (j >= 0 && P[i] != P[j]) j = b[j]; // if different, reset j using b
      i++; j++; // if same, advance both pointers
      b[i] = j; // observe i = 8, 9, 10, 11, 12 with j = 0, 1, 2, 3, 4
  	} 
	}           // in the example of P = "SEVENTY SEVEN" above

  static void kmpSearch() { // this is similar as kmpPreprocess(), but on string T
		int i = 1, j = 0; // starting values
    while (i < n) { // search through string T
      while (j >= 0 && T[i] != P[j])
        j = b[j]; // if different, reset j using b
      i++; j++; // if same, advance both pointers
      if (j == m) { // a match found when j == m
        System.out.println(m/(i-m));
        j = b[j]; // prepare j for the next possible match
  		  break;
      }		 
		} 
	}

  public static void main(String[] args) throws IOException{
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    
    while (true) {
      String S = in.readLine();
      if (S.equals(".")) break;

      P = S.toCharArray();
      T = (S+S).toCharArray();
      n = T.length;
      m = P.length;

      kmpPreprocess();
      kmpSearch();
    }  
  }
}
