#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include<climits>
#include<cmath>
#include<stack>
using namespace std;


class segment_tree {
  private:
    vector<int> min_heap;
    vector<int> max_heap;
    vector<int> lazy;
    int n; // size of underlying array

    void build(vector<int>& arr, int ss, int se, int si) {
      if (ss > se) return; // out of range

      if (ss == se) { // leaf
        min_heap[si] = arr[ss];
        max_heap[si] = arr[ss];
        return;
      }

      int mid = (ss+se)/2;
      build(arr, ss, mid, si*2+1);
      build(arr, mid+1, se, si*2+2);

      min_heap[si] = min(min_heap[si*2+1], min_heap[si*2+2]);
      max_heap[si] = max(max_heap[si*2+1], max_heap[si*2+2]);
    }

    /*
     * Runs query on array[i...j] where
     * [i, j] = [ss, se] intersect [us, ue]
     * si is the index of the node representing segment ss, se]
     */
    void update(int si, int ss, int se, int us, int ue, int diff) {
      fix(si, ss, se);

      if (disjoint(ss, se, us, ue)) return;

      if (subset(ss, se, us, ue)) {
        min_heap[si] += diff;
        max_heap[si] += diff;

        if (ss != se) {
          // lazily update children
          lazy[si*2+1] += diff;
          lazy[si*2+2] += diff;
        }
        return;
      }

      // [ss, se] has some intersection with [us, ue]
      int mid = (ss+se)/2;
      update(si*2+1, ss, mid, us, ue, diff);
      update(si*2+2, mid+1, se, us, ue, diff);

      min_heap[si] = min(min_heap[si*2+1], min_heap[si*2+2]);
      max_heap[si] = max(max_heap[si*2+1], max_heap[si*2+2]);
    }

    /*
     * Returns query result on array[i...j] where
     * [i, j] = [ss, se] intersect [qs, qe].
     * si is the index of the node representing segment [ss, se]
     */
    int query(int ss, int se, int qs, int qe, int si, bool is_min_query) {
      fix(si, ss, se);

      if (disjoint(ss, se, qs, qe)) return is_min_query? INT_MAX : INT_MIN;

      if (subset(ss, se, qs, qe)) return is_min_query? min_heap[si] : max_heap[si];

      // [ss, se] and [qs, qe] have some intersection
      int mid = (ss+se)/2;

      int left_query = query(ss, mid, qs, qe, 2*si+1, is_min_query);
      int right_query = query(mid+1, se, qs, qe, 2*si+2, is_min_query);

      return is_min_query? min(left_query, right_query) : max(left_query, right_query);
    }

    bool disjoint(int ss, int se, int qs, int qe) {
      return ss > se || ss > qe || se < qs;
    }

    bool subset(int ss, int se, int qs, int qe) {
      return ss >= qs && se <= qe;
    }

    void fix(int si, int ss, int se) {
      if (lazy[si]) {
        // make pending updates to node
        min_heap[si] += lazy[si];
        max_heap[si] += lazy[si];

        // lazily update children
        if (ss != se) {
          lazy[si*2+1] += lazy[si];
          lazy[si*2+2] += lazy[si];
        }

        lazy[si] = 0;
      }
    }

  public:
    segment_tree(vector<int> arr) {
      n = arr.size();
      int nodes = 2*pow(2, ceil(log2(n))) - 1; // # nodes <= 2*2^ceil(lg(n)) - 1
      min_heap = vector<int>(nodes);
      max_heap = vector<int>(nodes);
      lazy = vector<int>(nodes);
      build(arr, 0, n-1, 0);
    }

    void update(int us, int ue, int diff) {
      update(0, 0, n-1, us, ue, diff);
    }

    int min_query(int qs, int qe) {
      if (qs < 0 || qe > n-1 || qs > qe) {
        throw "INVALID_QUERY_INPUT";
      }
      return query(0, n-1, qs, qe, 0, true);
    }

    int max_query(int qs, int qe) {
      if (qs < 0 || qe > n-1 || qs > qe) {
        throw "INVALID_QUERY_INPUT";
      }
      return query(0, n-1, qs, qe, 0, false);
    }
};

void preorder(vector<list<int>>& children, int node, vector<int>& preorder_id) {
  stack<int> s;
  s.push(node);
  int i = 1;

  while (!s.empty()) {
    node = s.top(); s.pop();
    preorder_id[node] = i++;
    for (auto it = children[node].rbegin(); it != children[node].rend(); ++it) {
      s.push(*it);
    }
  }
}

void solve(int n) {
  vector<list<int>> children(n);
  vector<int> numDirectChildren(n);
  vector<int> numNodesInSubtree(n, 1);
  vector<int> parent(n);
  parent[0] = -1;
  for (int i = 1; i < n; i++) {
    int tmp;
    cin >> tmp;
    parent[i] = tmp - 1;
    children[parent[i]].push_back(i);
    numDirectChildren[parent[i]]++;
  }
  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (numDirectChildren[i] == 0)
      q.push(i);
  }
  while (!q.empty()) {
    int curr = q.front(); q.pop();
    if (parent[curr] < 0) break;
    numNodesInSubtree[parent[curr]] += numNodesInSubtree[curr];
    if (--numDirectChildren[parent[curr]] == 0)
      q.push(parent[curr]);
  }
  vector<int> startInterval(n);
  q.push(0);
  while (!q.empty()) {
    int curr = q.front(); q.pop();
    int currStart = startInterval[curr]+1;
    for (int child : children[curr]) {
      startInterval[child] = currStart;
      currStart += numNodesInSubtree[child];
      q.push(child);
    }
  }

  vector<int> x(n);
  segment_tree T(x);

  for (int i = 0; i < n; i++)  {
    int salary;
    cin >> salary;
    T.update(startInterval[i], startInterval[i], salary);
  }

  int Q;
  cin >> Q;

  // answer queries
  for (int q = 0; q < Q; q++) {
    char type;
    int emp_id;
    cin >> type >> emp_id;
    emp_id--; // 0-based index
    int range_end = startInterval[emp_id] + numNodesInSubtree[emp_id] - 1;
    if (type == 'R') {
      int amount;
      cin >> amount;
      T.update(startInterval[emp_id], range_end, amount);
    } else { // type == 'Q'
      cout << T.max_query(startInterval[emp_id], range_end) - T.min_query(startInterval[emp_id], range_end) << endl;
    }
  }
}

int main() {
  int T, N;
  cin >> T;

  for (int test = 0; test < T; test++) {
    cin >> N;
    solve(N);
  }
}
