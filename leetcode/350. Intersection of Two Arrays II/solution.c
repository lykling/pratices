#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size,
               int *returnSize) {
  int a[1001];
  int b[1001];
  memset(a, 0, sizeof(a));
  memset(b, 0, sizeof(b));

  int max = 0;
  for (int i = 0; i < nums1Size; ++i) {
    a[nums1[i]]++;
    if (nums1[i] > max) {
      max = nums1[i];
    }
  }
  for (int i = 0; i < nums2Size; ++i) {
    b[nums2[i]]++;
    if (nums2[i] > max) {
      max = nums2[i];
    }
  }

  int *result = (int *)malloc(sizeof(int) * 1001);
  *returnSize = 0;
  for (int i = 0; i < max + 1; ++i) {
    if (a[i] > 0 && b[i] > 0) {
      int count = a[i] < b[i] ? a[i] : b[i];
      for (int j = 0; j < count; ++j) {
        result[*returnSize] = i;
        (*returnSize)++;
      }
    }
  }
  return result;
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  int nums1[] = {1, 2, 2, 1};
  int nums2[] = {2, 2};
  int returnSize;
  int *result = intersect(nums1, 4, nums2, 2, &returnSize);
  for (int i = 0; i < returnSize; ++i) {
    printf("%d ", result[i]);
  }
  free(result);

  return EXIT_SUCCESS;
}
