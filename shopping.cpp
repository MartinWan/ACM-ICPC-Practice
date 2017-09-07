#include<iostream>
#include<algorithm>
#include<climits>
#include<vector>
#include<cmath>
using namespace std;


/*
 * A segment tree is a data structure for efficiently running 
 * an aggregate query on an array segment array[start...end] and
 * efficiently updating an array segment array[start...end]. 
 * Both update() and query() have O(logN) performance, where N is the size
 * of the underlying array.
 *
 * This implementation is built to answer range min and range max queries
 * but can be easily modified to answer range sum queries. Code
 * is based off of post by GeeksForGeeks: http://www.geeksforgeeks.org/lazy-propagation-in-segment-tree/
 */
template<class T>
class segment_tree {
  private:
    vector<T> min_heap; // full binary tree stored in an array. Nodes are the aggregate of their two children (array value if leaf)
 //   vector<T> max_heap; 
 //   vector<T> lazy; // lazy[i] = pending updates on node i
    int n; // size of underlying array, i.e. number of leaves

    void build(vector<T>& arr, int ss, int se, int si) {
      if (ss > se) return; // out of range

      if (ss == se) { // leaf
        min_heap[si] = arr[ss];
   //     max_heap[si] = arr[ss];
        return;
      }

      int mid = (ss+se)/2;
      build(arr, ss, mid, si*2+1);
      build(arr, mid+1, se, si*2+2);

      min_heap[si] = min(min_heap[si*2+1], min_heap[si*2+2]);
     // max_heap[si] = max(max_heap[si*2+1], max_heap[si*2+2]);
    }

    /*
     * Runs query on array[i...j] where
     * [i, j] = [ss, se] intersect [us, ue]
     * si is the index of the node representing segment ss, se]
     */
    void update(int si, int ss, int se, int us, int ue, T diff) {
 /*     fix(si, ss, se);

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
      max_heap[si] = max(max_heap[si*2+1], max_heap[si*2+2]); */
    }

    /*
     * Returns query result on array[i...j] where
     * [i, j] = [ss, se] intersect [qs, qe].
     * si is the index of the node representing segment [ss, se]
     */
     T query(int ss, int se, int qs, int qe, int si, bool is_min_query) {
     // fix(si, ss, se);

      if (disjoint(ss, se, qs, qe)) return numeric_limits<T>::max();

      if (subset(ss, se, qs, qe)) return min_heap[si];

      // [ss, se] and [qs, qe] have some intersection
      int mid = (ss+se)/2;

      T left_query = query(ss, mid, qs, qe, 2*si+1, is_min_query);
      T right_query = query(mid+1, se, qs, qe, 2*si+2, is_min_query);

      return min(left_query, right_query);
      // return is_min_query? min(left_query, right_query) : max(left_query, right_query);
    }

    bool disjoint(int ss, int se, int qs, int qe) {
      return ss > se || ss > qe || se < qs;
    }

    bool subset(int ss, int se, int qs, int qe) {
      return ss >= qs && se <= qe;
    }

    void fix(int si, int ss, int se) {
      //if (lazy[si]) {
        // make pending updates to node
        //min_heap[si] += lazy[si];
     //   max_heap[si] += lazy[si];

        // lazily update children
        //if (ss != se) {
          //lazy[si*2+1] += lazy[si];
          //lazy[si*2+2] += lazy[si];
        //}

        //lazy[si] = 0;
     // }
    }

  public:
    segment_tree(vector<T> arr) {
      n = arr.size();
      int nodes = 2*pow(2, ceil(log2(n))) - 1; // # nodes <= 2*2^ceil(lg(n)) - 1
      min_heap = vector<T>(nodes);
     // max_heap = vector<T>(nodes);
     // lazy = vector<T>(nodes);
      build(arr, 0, n-1, 0);
    }

    void update(int us, int ue, T diff) {
      update(0, 0, n-1, us, ue, diff);
    }

    T min_query(int qs, int qe) {
   //   if (qs < 0 || qe > n-1 || qs > qe) {
     //   throw logic_error("Bad call to min_query");
     // }
      return query(0, n-1, qs, qe, 0, true);
    }

    T max_query(int qs, int qe) {
     // if (qs < 0 || qe > n-1 || qs > qe) {
       // throw logic_error("Bad call to max_query");
     // }
      return query(0, n-1, qs, qe, 0, false);
    }
};


int main() {
  int n, q;
  cin >> n >> q;
  vector<long long> a(n);
  
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

	segment_tree<long long> T(a);  

  for (int i = 0; i < q; i++) {
    int l, r;
    long v;
    cin >> v >> l >> r;
    l--; r--;
    
    while (l <= r) { 
      int imin = l; 
      int imax = r;

      while(imin < imax) {
        int imid = (imin+imax)/2;
        if (T.min_query(l, imid) > v) imin = imid+1;
        else imax = imid;
      }
      
      if (imin > r) break;
      if (a[imin] > v) break;

      v %= a[imin];
      l = imin + 1;
    }
      
    cout << v << endl;
  }
}
