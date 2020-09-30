#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

int find(int* nums, int l, int r, int t) {
  if (l > r) {
    return -1;
  }
  int m = (r - l) / 2 + l;
  int mm = nums[m];
  /* printf("find: l: %d, r: %d, m: %d\n", l, r, m); */
  if (nums[l] == t) {
    return l;
  }
  if (l == r) {
    if (mm == t) {
      return l;
    }
    return -1;
  }
  if (mm > nums[r]) {
    if (mm > t) {
      int left = find(nums, l, m - 1, t);
      int right = find(nums, m + 1, r, t);
      if (left != -1) {
        return left;
      }
      if (right != -1) {
        return right;
      }
      return -1;
    } else if (mm < t) {
      return find(nums, m + 1, r, t);
    } else {
      return find(nums, l, m, t);
    }
  } else if (mm < nums[l]) {
    if (mm < t) {
      int left = find(nums, l, m - 1, t);
      int right = find(nums, m + 1, r, t);
      if (left != -1) {
        return left;
      }
      if (right != -1) {
        return right;
      }
      return -1;
    } else if (mm > t) {
      return find(nums, l, m - 1, t);
    } else {
      return find(nums, l, m, t);
    }
  } else {
    if (mm >= t) {
      return find(nums, l, m, t);
    } else {
      return find(nums, m + 1, r, t);
    }
  }
}

int search(int* nums, int n, int t) {
  return find(nums, 0, n - 1, t);
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
      printf("%d%c", nums[i], i == n - 1 ? '\n': ' ');
    }
    printf("search: %d\n", search(nums, n, t));
    free(nums);
  }
  return EXIT_SUCCESS;
}
