#include <stdio.h>
#include <stdlib.h>


int reverse(int x) {
  int y = 0;
  while (x) {
    if (y > 214748364 || y < -214748364) {
      return 0;
    }
    y = y * 10 + x % 10;
    x = x / 10;
  }
  return y;
}


int main(int argc, char **argv) {
  int x;
  while (scanf("%d", &x) != EOF) {
    printf("%d\n", reverse(x));
  }
  return EXIT_SUCCESS;
}
