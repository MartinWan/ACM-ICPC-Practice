#include <stdio.h>
#include <set>
#define N_MAX 10000
using namespace std;

int memo[N_MAX+1];

set<int> primeFactors(int N) {
  set<int> factors;

  while (N % 2 == 0) {
    factors.insert(2);
    N /= 2;
  }

  for (int i = 3; i*i <= N; i += 2) {
    while (N % i == 0) {
      factors.insert(i);
      N /= i;
    }
  }

  if (N > 2)
    factors.insert(N);

  return factors;
}


int phi(int N) {
  int result = N;

  for (int p : primeFactors(N)) 
    result *= 1 - 1.0/p;

  return result;
}

int seqLength(int N) {
  if (memo[N] == 0) {
    if (N == 2) 
      memo[N] = 3;
    else
      memo[N] = seqLength(N-1) + phi(N);
  }

  return memo[N];
}

int main() {
  int P, K, N;

  scanf("%d", &P);

  for (int i = 0; i < P; i++) {
    scanf("%d %d", &K, &N);

    printf("%d %d\n", K, seqLength(N));
  }
}
