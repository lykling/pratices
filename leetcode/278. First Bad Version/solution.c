#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

static int target;
static int callcnt;

bool isBadVersion(int v) {
  ++callcnt;
  if (v >= target) {
    return true;
  }
  return false;
}

int findLeft(int l, int r) {
  int m = (r - l) / 2 + l;
  bool mm = isBadVersion(m);
  /* printf("l: %d, r: %d, m: %d\n", l, r, m); */
  if (l > r) {
    return -1;
  }
  if (mm) {
    if (m == l) {
      return m;
    }
    return findLeft(l, m);
  } else {
    return findLeft(m + 1, r);
  }
}

int firstBadVersion(int n) {
  int target = findLeft(1, n);
  return target;
}

int main(int argc, char** argv) {
  int n, t;
  while (scanf("%d %d", &n, &t) != EOF) {
    target = t;
    callcnt = 0;
    printf("first: %d\n", firstBadVersion(n));
    printf("callcnt: %d\n", callcnt);
  }
  return EXIT_SUCCESS;
}
