#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>

void swap(int* arr, int a, int b) {
  int tmp = arr[a];
  arr[a] = arr[b];
  arr[b] = tmp;
}

void swim(int* arr, int p) {
  while (p) {
    int pp = (p - 1) / 2;
    if (arr[p] < arr[pp]) {
      swap(arr, pp, p);
    }
    p = pp;
  }
}

void sink(int* arr, int p, int n) {
  int l = (p + 1) * 2 - 1;
  int r = l + 1;
  while (l < n || r < n) {
    if (r >= n) {
      if (arr[p] > arr[l]) {
        swap(arr, p, l);
        p = l;
      } else {
        break;
      }
    } else if (arr[l] <= arr[r]) {
      if (arr[p] > arr[l]) {
        swap(arr, p, l);
        p = l;
      } else {
        break;
      }
    } else {
      if (arr[p] > arr[r]) {
        swap(arr, p, r);
        p = r;
      } else {
        break;
      }
    }
    l = (p + 1) * 2 - 1;
    r = l + 1;
  }
}

int findKthLargest(int *nums, int n, int k) {
  int arr[k];
  int i;
  int p = 0;
  for (i = 0; i < n; ++i) {
    if (p < k) {
      arr[p++] = nums[i];
      swim(arr, p - 1);
    } else {
      if (nums[i] > arr[0]) {
        arr[0] = nums[i];
        sink(arr, 0, k);
      }
    }
  }
  return arr[0];
}

int main(int argc, char** argv) {
  int n, i, k;
  int* nums;
  while (scanf("%d", &n) != EOF) {
    nums = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    scanf("%d", &k);
    printf("findKthLargest: %d\n", findKthLargest(nums, n, k));
    free(nums);
  }
  return EXIT_SUCCESS;
}
