#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int candy(int* ratings, int ratingsSize){
  int ll[ratingsSize];
  int rr[ratingsSize];
  int i = 0;
  int s = 0;
  memset(ll, 0, sizeof(int) * ratingsSize);
  memset(rr, 0, sizeof(int) * ratingsSize);
  for (i = 1; i < ratingsSize; ++i) {
    if (ratings[i] > ratings[i - 1]) {
      ll[i] = ll[i - 1] + 1;
    }
  }
  for (i = ratingsSize - 2; i >= 0; --i) {
    if (ratings[i] > ratings[i + 1]) {
      rr[i] = rr[i + 1] + 1;
    }
  }
  for (i = 0; i < ratingsSize; ++i) {
    s += ll[i] > rr[i] ? ll[i] : rr[i];
  }
  return s + ratingsSize;
}

int main(int argc, char* argv) {
  int a1[] = {1, 0, 2};
  printf("a1: %d\n", candy(a1, 3));
  int a2[] = {1, 2, 2};
  printf("a2: %d\n", candy(a2, 3));
  return EXIT_SUCCESS;
}
