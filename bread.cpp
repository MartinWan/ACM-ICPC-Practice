#include<iostream>
#include<vector>
using namespace std;

/**
 * Problem: https://open.kattis.com/problems/bread
 *
 * Accepted in 0.09 s. Key observation is that when applying the “paddle trick” to the array, the number of changes to 
 * the relative order of each pair of integers can only be increased/decreased by 2. This problem is thus equivalent to
 * checking if the # of inversions in the array is even or odd, which can be done in O(NlogN) using a merge sort.
 *
 */

int merge_sort(vector<int>& a, int l, int r) {
  int size = r - l + 1;
  if (size <= 1) return 0; // consider size arrays of size 0, 1 sorted

  int inv = 0;

  int mid = (l + r) / 2;
  
  inv += merge_sort(a, l, mid);
  inv += merge_sort(a, mid+1, r);
  
  vector<int> temp(size); // temp array to merge a[l...mid] and a[mid+1...r]

  int i = l; // current index of a[l...mid]
  int j = mid+1; // curent index of a[mid+1...r]
  for (int k = 0; k < size; k++) {
    int x;
    if (i > mid) {
      x = a[j++];
    }
    else if (j > r)
      x = a[i++];
    else {
      if (a[i] < a[j]) 
        x = a[i++];
      else {
        x = a[j++];
        inv += mid-i+1;
      }
    }
    temp[k] = x;
  }
  
  // copy merged array into a[l...r]
  for (int i = l, k = 0; i <= r; i++, k++) {
    a[i] = temp[k];
  }

  return inv;
}

int merge_sort(vector<int>& a) {
  return merge_sort(a, 0, a.size()-1);
}

int main() {
  int n;
  cin >> n;
  
  vector<int> start(n);
  for (int i = 0; i < n; i++) {
    cin >> start[i];
  }

	vector<int> end(n);
  for (int i = 0; i < n; i++) {
    cin >> end[i];
  }

  // normalize
  vector<int> end_idx(n+1);  
  for (int i = 0; i < n; i++) {
    end_idx[end[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    int num = start[i-1];
    start[i-1] = i;
    end[end_idx[num]] = i;
  }
  
	int inv = merge_sort(end);
  if (inv % 2 == 0) cout << "Possible" << endl;
  else cout << "Impossible" << endl;
}
