#include <stdio.h>
#include <stdlib.h>


int firstMissingPositive(int* nums, int n) {
  int x;
  int swap;
  for (x = 0; x < n;) {
    if (nums[x] != x + 1 && nums[x] > 0 && nums[x] <= n && nums[nums[x] - 1] != nums[x]) {
      swap = nums[nums[x] - 1];
      nums[nums[x] - 1] = nums[x];
      nums[x] = swap;
    } else {
      ++x;
    }
  }
  for (x = 0; x < n; ++x) {
    if (nums[x] != x + 1) {
      break;
    }
  }
  return x + 1;
}


int main(int argc, char **argv) {
  int n;
  int i;
  int* nums = malloc(sizeof(int) * 20);
  while (scanf("%d", &n) != EOF) {
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    for (i = 0; i < n; ++i) {
      printf("%d ", *(nums + i));
    }
    printf("\n");
    printf("%d\n", firstMissingPositive(nums, n));
  }
  return EXIT_SUCCESS;
}
