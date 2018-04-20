#include <stdio.h>
#include <stdlib.h>


int countPrimes(int n) {
  int *tag = malloc(sizeof(int) * n);
  int i, p;
  int count = 0;
  for (i = 2; i < n; ++i) {
    count += !tag[i];
    for (p = 2; p * i < n; tag[p++ * i] = 1);
  }
  return count;
}


int main(int argc, char **argv) {
  printf("%d\n", countPrimes(20));
  return EXIT_SUCCESS;
}
