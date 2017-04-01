#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int* cache;

int trans_count(int n) {
  int result;
  if (n < 10000 && cache[n] != -1) {
    result = cache[n];
  } else if ((n & 1) ^ 1) {
    result = trans_count(n >> 1) + 1;
  } else {
    result = trans_count((n << 1) + n + 1) + 1;
  }
  (n < 10000) && (cache[n] = result);
  return result;
}

int main(int argc, char** argv) {
  int i, j, k, upper, lower;
  int max;
  cache = (int*)malloc(sizeof(int) * 10000);
  memset(cache, -1, sizeof(int) * 10000);
  cache[0] = 0;
  cache[1] = 1;
  while (scanf("%d %d", &i, &j) != EOF) {
    lower = i < j ? i : j;
    upper = i < j ? j : i;
    for (max = 0, k = lower; k <= upper; ++k) {
      if (trans_count(k) > max) {
        max = trans_count(k);
      }
    }
    printf("%d %d %d\n", i, j, max);
  }
  return EXIT_SUCCESS;
}
