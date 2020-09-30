#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int divide(int dividend, int divisor) {
  int sign = 1;
  long a = dividend;
  long b = divisor;
  if (dividend < 0) {
    sign = -sign;
    a = -a;
  }
  if (divisor < 0) {
    sign = -sign;
    b = -b;
  }
  long tmp[33] = {0};
  tmp[0] = b;
  int p = 0;
  long result = 0;
  long left = a;
  while (p >= 0 && left > 0) {
    /* printf("p:%d tmp[%d]:%d left:%d\n", p, p, tmp[p], left); */
    if (tmp[p] <= left) {
      result += (1 << p);
      left -= tmp[p];
      tmp[p + 1] = tmp[p] + tmp[p];
      ++p;
    } else {
      --p;
    }
  }
  if (sign > 0) {
    if (result > 0x7fffffff) {
      return 0x7fffffff;
    }
    return (int)result;
  }
  if (result > 0x100000000) {
    return 0x7fffffff;
  }
  return (int)(-result);
}

int main(int argc, char** argv) {
  int i, n;
  int dividend, divisor;
  printf("%d\n", 0x7fffffff);
  scanf("%d", &n);
  printf("test case: %d\n", n);
  for (i = 0; i < n; ++i) {
    scanf("%d %d", &dividend, &divisor);
    printf("case[%d]: %d %d\n", i, dividend, divisor);
    printf("output: %d\n", divide(dividend, divisor));
    // printf("output: %d\n", dividend / divisor);
    printf("----------\n");
  }
  return EXIT_SUCCESS;
}
