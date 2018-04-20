#include <stdio.h>
#include <stdlib.h>


int nthUglyNumber(int n) {
  int *u = malloc(sizeof(int) * n);
  int i;
  int p2 = 0;
  int p3 = 0;
  int p5 = 0;
  int a, b, c;
  if (n < 1) {
    return 0;
  }
  if (n < 2) {
    return n;
  }
  u[0] = 1;
  for (i = 1; i < n; ++i) {
    a = u[p2] * 2;
    b = u[p3] * 3;
    c = u[p5] * 5;
    if (a <= b && a <= c) {
      u[i] = a;
      ++p2;
      if (b == a) ++p3;
      if (c == a) ++p5;
    } else if (b <= c) {
      u[i] = b;
      ++p3;
      if (c == b) ++p5;
    } else {
      u[i] = c;
      ++p5;
    }
  }
  return u[n - 1];
}

int main(int argc, char **argv) {
  int i = 0;
  for (i = 0; i < 1690; ++i) {
    printf("%d\n", nthUglyNumber(i));
  }
  return EXIT_SUCCESS;
}
