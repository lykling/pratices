#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
  int x;
  while (scanf("%d", &x) != EOF && x != 42) {
    printf("%d\n", x);
  }
  return EXIT_SUCCESS;
}
