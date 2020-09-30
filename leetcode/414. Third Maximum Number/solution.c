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

int kMax(int *nums, int n, int k) {
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

int thirdMax(int* nums, int n) {
  int arr[3];
  int p = 0;
  int pp;
  int i;
  for (i = 0; i < n; ++i) {
    if (p < 3) {
      for (pp = p - 1; pp >= 0 && arr[pp] != nums[i]; --pp) {}
      if (pp < 0) {
        arr[p++] = nums[i];
        for (pp = p - 2; pp >= 0 && arr[pp] < nums[i]; --pp) {
          if (pp < 2) {
            arr[pp + 1] = arr[pp];
          }
          arr[pp] = nums[i];
        }
      }
    } else {
      for (pp = p - 1; pp >= 0 && arr[pp] != nums[i]; --pp) {}
      if (pp < 0) {
        for (pp = p - 1; pp >= 0 && arr[pp] < nums[i]; --pp) {
          if (pp < 2) {
            arr[pp + 1] = arr[pp];
          }
          arr[pp] = nums[i];
        }
      }
    }
  }
  if (p == 3) {
    return arr[p - 1];
  }
  return arr[0];
}

int main(int argc, char** argv) {
  int n, i;
  int* nums;
  while (scanf("%d", &n) != EOF) {
    nums = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    printf("thirdMax: %d\n", thirdMax(nums, n));
    free(nums);
  }
  return EXIT_SUCCESS;
}
