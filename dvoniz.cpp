#include <iostream>
#include <limits.h>

using namespace std;

/**
  * Problem: https://open.kattis.com/problems/dvoniz
**/

int N;
int S;
int A[100000];
long P[100003];

void initPrefixSums() {
  int iPrefixSum = 0;
  for (int i = 0; i < N; i++) {
    P[i] = iPrefixSum;
    iPrefixSum += A[i];
  }
  P[N] = iPrefixSum;
  P[N+1] = LONG_MAX; // add padding so we don't have to worry about array indexes
  P[N+2] = LONG_MAX;
}

void dvoniz() {
 initPrefixSums(); // P[i] is the sum of A[0..i-1] 
 int j = -1; // A[i,j] is an interesting subsequence starting at i 

 for (int i = 0; i < N; i++) {
   while (P[j+1] - P[i] < 2*S) {
     j += 2;
   }
   int k = (i + j) / 2;
   while (P[k+1] - P[i] > S || P[j+1] - P[k+1] > S) {
     j -= 2;
     k = (i + j) / 2;
   }
   cout << j - i + 1 << endl;
   j = max(j - 1, i);
 }
}

int main() {
  cin >> N;
  cin >> S;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  dvoniz();
}
