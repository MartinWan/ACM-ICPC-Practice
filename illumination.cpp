#include <iostream>
#include<list>
#include <vector>
using namespace std;
typedef long long num;

/*
 * Solves the 2-SAT problem in linear time.
 * Represented as a class since it is common to "build up"
 * the boolean formula across loops, functions etc.
 */
class two_sat {
	private:
		int V;
		vector<vector<int>> G;
		vector<vector<int>> G_T;

		void visit(int u, list<int>& order, vector<bool>& visited) {
			if (!visited[u]) {
				visited[u] = true;

				for (int v : G[u]) {
					visit(v, order, visited);
				}

				order.push_front(u);
			}
		}

		void assign(int u, int color, vector<int>& component) {
			component[u] = color;
			for (auto i = 0u; i < G_T[u].size(); i++) {
				int v = G_T[u][i];
				if (component[v] == -1) assign(v, color, component);
			}
		}

		void add(int x, int y) { G[x].push_back(y); };

	public:
    /*
     * initializes 2-SAT problem with a maximum of n conjunctions
     * e.g. (x1 or y1) && (x2 or y2) && ... && (xn or yn)
     */
		two_sat(int n) {
			V = 2*n;
			G = vector<vector<int>>(V);
			G_T = vector<vector<int>>(V);
		}

		bool satisfiable(vector<bool>& values) {
			list<int> L; // contains vertices in reverse post order i.e. "topological" order
			vector<bool> visited(V);
			for (int v = 0; v < V; v++) visit(v, L, visited);

			// generate transpose of G
			for (int v = 0; v < V; v++) for (int u = 0; u < G[v].size(); u++)
				G_T[G[v][u]].push_back(v);
			
			// considering vertices in topological order, 
			// label strongly connected components using DFS on G transposed
			int color = 0;
			vector<int> component = vector<int>(V, -1);
			for (int u : L) {
				if (component[u] == -1) assign(u, color++, component);
			}

			for (int v = 0; v < V; v++) 
        if (component[v] == component[v^1])  // satisfiable iff all xi and !xi separate components
          return false; 			
      for (int v = 0; v < V; v+=2) 
        values[v/2] = (component[v] > component[v^1]); // xi == 1, iff xi comes after !xi in topological order

			return true;
		}

		/*
		 * Add disjunction of form (a or b) to the SAT formula
		 * if type = 0, add (a or b)
		 * if type = 1, add (!a or b)
		 * if type = 2, add (a or !b)
		 * if type = 3, add (!a or !b)
		 */
		void add_disjunction(int x, int y, int type) {
			int a=2*x, na=2*x+1, b=2*y, nb=2*y+1;
			switch (type) {
				case 0: add(na, b); add(nb, a); break; // a or b <=> !a -> b <=> !b -> a
				case 1: add(a, b); add(nb, na); break; // !a or b <=> a -> b <=> !b -> !a
				case 2: add(na, nb); add(b, a); break; // a or !b <=> !a -> !b <=> b -> a
				case 3: add(a, nb); add(b, na); break; // !a or !b <=> a -> !b <=> b -> !a
				default: throw logic_error("add_disjunction() requires type to be 0, 1, 2, or 3");
			}
		}
};



int main() {
	int n, r, l;
	cin >> n >> r >> l;

	vector<int> px(l);
	vector<int> py(l);
	for (int i = 0; i < l; i++) {
		cin >> px[i] >> py[i];
	}

	two_sat S(2*l);
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < l; j++) {
			if (i == j) continue;
			int xi = px[i];  int yi = py[i];
			int xj = px[j]; int yj = py[j];

			if (yi == yj && abs(xi-xj) < 2*r-1) {
				S.add_disjunction(i, j, 3);
			}
			if (xi == xj && abs(yj-yi) < 2*r-1) {
				S.add_disjunction(i, j, 0);
			}
		}
	}

	vector<bool> values(2*l);
	bool possible=S.satisfiable(values);
	if (possible) printf("YES\n");
	else printf("NO\n");
}
