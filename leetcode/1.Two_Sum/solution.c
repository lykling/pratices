#include <stdio.h>
#include <stdlib.h>


int* twoSum(int* nums, int numsSize, int target) {
  int i, j;
  int* result = (int*)malloc(sizeof(int) * 2);
  for (i = 0; i < numsSize; ++i) {
    for (j = i + 1; j < numsSize; ++j) {
      if (nums[i] + nums[j] == target) {
        result[0] = i;
        result[1] = j;
        return result;
      }
    }
  }
  return result;
}


int main(int argc, char **argv) {
  int i;
  int size;
  int target;
  int* nums = (int*)malloc(sizeof(int) * 100);
  int* result = (int*)malloc(sizeof(int) * 2);
  scanf("%d %d", &size, &target);
  for (i = 0; i < size; ++i) {
    scanf("%d", nums + i);
  }
  result = twoSum(nums, size, target);
  printf("%d %d\n", result[0], result[1]);
  return EXIT_SUCCESS;
}
