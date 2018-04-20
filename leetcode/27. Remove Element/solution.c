#include <stdio.h>
#include <stdlib.h>


int removeElement(int* nums, int numsSize, int val) {
  int i = 0;
  int j = numsSize;
  for (i = 0; i < j; ++i) {
    for (; i < j && nums[i] == val; --j) {
      nums[i] ^= nums[j - 1];
      nums[j - 1] ^= nums[i];
      nums[i] ^= nums[j - 1];
    }
  }
  return j;
}


int main(int argc, char **argv) {
  int arr[] = {3, 2, 2, 3};
  int i = 0;
  int len = 4;
  len = removeElement(arr, 4, 3);
  for (i = 0; i < len; ++i) {
    printf("%d%c", arr[i], i == len - 1 ? '\n' : ' ');
  }
  return EXIT_SUCCESS;
}
