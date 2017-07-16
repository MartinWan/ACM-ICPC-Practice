#include <stdio.h>
#include <string>
#define MAX_N 10000

// problem https://open.kattis.com/problems/happyprime

using namespace std;

int P;
bool visited[MAX_N+1];

bool is_happy(int N) {
  while (N != 1) {
    if (!visited[N]) {
      visited[N] = true;

      string digits = to_string(N);

      N = 0;
      for (int i = 0; i < digits.length(); i++) {
        int temp = digits[i] - '0';
        N += temp * temp;
      }
    } else {
      return false;
    }
  }

  return true;
}

bool is_prime(int N) {
  if (N < 2)
    return false;

  if (N == 2)
    return true;

  if (N % 2 == 0)
    return false;

  for (int i = 3; i*i <= N; i += 2) {
    if (N % i == 0)
      return false;
  }

  return true;
}

int main() {
  int K, N;
  scanf("%d", &P);


  for (int i = 0; i < P; i++) {
    scanf("%d %d", &K, &N);
 
    for (int i = 1; i <= MAX_N; i++)
      visited[i] = false;

    printf("%d %d %s\n", K, N, (is_prime(N) && is_happy(N))? "YES": "NO");
  }
}
