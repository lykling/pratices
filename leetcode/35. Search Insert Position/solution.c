#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

int findLeft(int* nums, int l, int r, int t) {
  int m = (r - l) / 2 + l;
  int mm = nums[m];
  if (m == l) {
    if (mm >= t) {
      return m;
    }
    if (nums[r] >= t) {
      return r;
    }
    return r + 1;
  }
  if (mm > t) {
    return findLeft(nums, l, m - 1, t);
  } else {
    return findLeft(nums, m, r, t);
  }
}

int searchInsert(int* nums, int n, int t) {
  return findLeft(nums, 0, n - 1, t);
}

int main(int argc, char** argv) {
  int i, n, t;
  int* nums;
  while (scanf("%d", &n) != EOF) {
    nums = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    scanf("%d", &t);
    printf("index: %d\n", searchInsert(nums, n, t));
    free(nums);
  }
  return EXIT_SUCCESS;
}
