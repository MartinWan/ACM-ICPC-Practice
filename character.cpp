#include <stdio.h>

int N;

int main() {
  scanf("%d", &N);
  
  printf("%d\n", (1 << N) - 1 - N);
}
