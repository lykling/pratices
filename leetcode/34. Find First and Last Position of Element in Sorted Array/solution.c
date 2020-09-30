#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int searchLeft(int* nums, int left, int right, int target) {
  int m = (left + right) / 2;
  /* printf("search left: left: %d, right: %d, m: %d\n", left, right, m); */
  int mm = nums[m];
  if (left > right) {
    return -1;
  }
  if (nums[left] == target) {
    return left;
  }
  if (left == right) {
    return -1;
  }
  if (mm >= target) {
    return searchLeft(nums, left, m, target);
  } else {
    return searchLeft(nums, m + 1, right, target);
  }
}

int searchRight(int* nums, int left, int right, int target) {
  int m = (left + right + 1) / 2;
  /* printf("search right: left: %d, right: %d, m: %d\n", left, right, m); */
  int mm = nums[m];
  if (left > right) {
    return -1;
  }
  if (nums[right] == target) {
    return right;
  }
  if (left == right) {
    return -1;
  }
  if (mm <= target) {
    return searchRight(nums, m, right, target);
  } else {
    return searchRight(nums, left, m - 1, target);
  }
}

int* searchRange(int* nums, int n, int target, int* retn) {
  *retn = 2;
  int* ret = (int*)malloc(sizeof(int) * *retn);
  ret[0] = -1;
  ret[1] = -1;
  if (n <= 0) {
    return ret;
  }
  int left = searchLeft(nums, 0, n - 1, target);
  int right = searchRight(nums, 0, n - 1, target);
  ret[0] = left;
  ret[1] = right;
  return ret;
}

int* searchRange2(int* nums, int n, int target, int* retn) {
  *retn = 2;
  int* ret = (int*)malloc(sizeof(int) * *retn);
  ret[0] = -1;
  ret[1] = -1;
  if (n <= 0) {
    return ret;
  }
  int left = searchLeft(nums, 0, n - 1, target);
  int right = left;
  if (left != -1) {
    while (right + 1 < n && nums[right + 1] == target) {
      ++right;
    }
  }
  ret[0] = left;
  ret[1] = right;
  return ret;
}

int* searchRange3(int* nums, int n, int target, int* retn) {
  *retn = 2;
  int* ret = (int*)malloc(sizeof(int) * *retn);
  ret[0] = -1;
  ret[1] = -1;
  if (n <= 0) {
    return ret;
  }
  int left = searchLeft(nums, 0, n - 1, target);
  int right = left;
  if (right != -1) {
    right = searchRight(nums, left, n - 1, target);
  }
  ret[0] = left;
  ret[1] = right;
  return ret;
}

int main(int argc, char** argv) {
  int n, t, i;
  int* nums;
  while (scanf("%d", &n) != EOF) {
    nums = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    scanf("%d", &t);
    printf("n: %d, t: %d\n", n, t);
    for (i = 0; i < n; ++i) {
      printf("%d%c", nums[i], i == n - 1 ? '\n' : ' ');
    }
    int retn;
    int* ret = searchRange3(nums, n, t, &retn);
    for (i = 0; i < retn; ++i) {
      printf("%d%c", ret[i], i == retn - 1 ? '\n' : ' ');
    }
    free(nums);
    free(ret);
  }
  return EXIT_SUCCESS;
}
