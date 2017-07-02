import java.util.*;

// https://open.kattis.com/problems/easyascab

class AsEasyAsCab {
	private static HashMap<Character, LinkedList<Charqacter>> G = new HashMap<>();
	private static HashMap<Character, Integer> incomingDegree = new HashMap<>();
	private static String[] words = new String[1000];

	private static Set<Character> zeroIncomingDegree() {
		Set<Character> S = new HashSet<>();
		for (char node: G.keySet()) {
			if (incomingDegree.get(node) == 0) {
				S.add(node);
			}
		}
		return S;
	}

	private static String uniqueOrder() {
		StringBuilder L = new StringBuilder();
		Set<Character> S = zeroIncomingDegree();

		while (S.size() == 1) {
			char node = S.iterator().next();
			L.append(node);
			
			incomingDegree.put(node, -1);

			for (char neighbor : G.get(node)) {
				incomingDegree.put(neighbor, incomingDegree.get(neighbor) - 1);
			}

			S = zeroIncomingDegree();
		}
		
		if (S.size() > 1) {
			return "AMBIGUOUS";
		} else { // size is 0
			if (L.length() == G.size()) { // we've added all characters
				return L.toString();
			} else { // still characters left and no more nodes of 0 incoming degree, so cycle
				return "IMPOSSIBLE";
			}
		}
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		String[] LN = in.nextLine().split(" ");
		char L = LN[0].charAt(0);
		int N = Integer.parseInt(LN[1]);
		
		// init graph
		for (char c = 'a'; c <= L; c++) {
			G.put(c, new LinkedList<>());
			incomingDegree.put(c, 0);
		}

		// create words
		for (int i = 0; i < N; i++) {
			words[i] = in.nextLine();
		}

		// create graph
		for (int i = 0; i < N - 1; i++) {
			String word1 = words[i];
			String word2 = words[i+1];
			int W = Math.min(word1.length(), word2.length());
			
			for (int j = 0; j < W; j++) {
				char c1 = word1.charAt(j);
				char c2 = word2.charAt(j);
				if (c1 != c2) {
					G.get(c1).add(c2); // add edge c1 -> c2
					incomingDegree.put(c2, incomingDegree.get(c2) + 1);
					break;
				}
			}
		}

		System.out.println(uniqueOrder());
	}
}
