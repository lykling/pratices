#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>

int removeDuplicates(int* nums, int n) {
  int p = 0;
  int pp = 0;
  int l = 0;
  int ll = 0;
  while (p < n) {
    if (p > 1 && nums[p] == l && nums[p] == ll) {
      ++p;
    } else {
      nums[pp++] = nums[p];
      ll = l;
      l = nums[p];
      ++p;
    }
  }
  return pp;
}

int main(int argc, char** argv) {
  int i, n;
  int* nums;
  while (scanf("%d", &n) != EOF) {
    nums = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    int ret = removeDuplicates(nums, n);
    for (i = 0; i < ret; ++i) {
      printf("%d%c", nums[i], i == ret - 1 ? '\n' : ' ');
    }
    free(nums);
  }
  return EXIT_SUCCESS;
}
