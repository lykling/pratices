#include <stdio.h>
#include <stdlib.h>


int trap(int* height, int size) {
  int drop = 0;
  int heigestidx = -1;
  int maxwallidx = -1;
  int maxwallheight = 0;
  int i;
  int wall = 0;
  for (i = 0; i < size; ++ i) {
    if (height[i]) {
      if (height[i] >= maxwallheight) {
        if (maxwallidx > -1) {
          drop += (i - maxwallidx - 1) * maxwallheight - wall;
        }
        maxwallidx = i;
        maxwallheight = height[i];
        wall = 0;
      } else {
        wall += height[i];
      }
    }
  }
  heigestidx = maxwallidx;
  wall = 0;
  maxwallidx = size;
  maxwallheight = 0;
  for (i = size - 1; i >= heigestidx; --i) {
    if (height[i]) {
      if (height[i] >= maxwallheight) {
        if (maxwallidx < size) {
          drop += (maxwallidx - i - 1) * maxwallheight - wall;
        }
        maxwallidx = i;
        maxwallheight = height[i];
        wall = 0;
      } else {
        wall += height[i];
      }
    }
  }
  return drop;
}


int main(int argc, char **argv) {
  int i;
  int j;
  int size_int = sizeof(int);
  int* l = (int*)malloc(size_int);
  // for (i = 0; scanf("%d", l + i) != EOF; ++i){}
  for (i = 0; scanf("%d", (l = (int*)realloc(l, size_int * (i + 1))) + i) != EOF; ++i) {}
  for (j = 0; j < i; ++j) {
    fprintf(stdout, "%d ", l[j]);
  }
  fprintf(stdout, "\n");
  fprintf(stdout, "%d\n", trap(l, i));
  return EXIT_SUCCESS;
}
