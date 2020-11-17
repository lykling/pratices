#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>

// O(n) with fixed size map
int findDuplicateWithMap(int* nums, int n) {
  char flag[4000];
  memset(flag, 0, sizeof(flag));
  for (int i = 0; i < n; ++i) {
    int x = nums[i] / 8;
    int y = nums[i] % 8;
    if (flag[x] & (1 << y)) {
      return nums[i];
    } else {
      flag[x] |= (1 << y);
    }
  }
  return nums[0];
}

// fast-slow point
int findDuplicate(int *nums, int n) {
  int a = nums[0];
  int b = nums[a];
  while (a != b) {
    a = nums[a];
    b = nums[nums[b]];
  }
  b = 0;
  while (b != a) {
    b = nums[b];
    a = nums[a];
  }
  return a;
}

int main(int argc, char** argv) {
  int i, n;
  int* nums;
  while (scanf("%d", &n) != EOF) {
    nums = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    printf("duplicate: %d\n", findDuplicate(nums, n));
    free(nums);
  }
  return EXIT_SUCCESS;
}
