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

typedef struct {
  int* nums;
  int size;
  int k;
} KthLargest;

int kthLargestAdd(KthLargest* obj, int val) {
  if (obj->size < obj->k) {
    obj->nums[obj->size++] = val;
    swim(obj->nums, obj->size - 1);
  } else {
    if (val > obj->nums[0]) {
      obj->nums[0] = val;
      sink(obj->nums, 0, obj->k);
    }
  }
  return obj->nums[0];
}

KthLargest* kthLargestCreate(int k, int* nums, int n) {
  KthLargest* obj = (KthLargest*)malloc(sizeof(KthLargest));
  obj->k = k;
  obj->nums = (int*)malloc(sizeof(int) * k);
  obj->size = 0;
  int i;
  for (i = 0; i < n; ++i) {
    kthLargestAdd(obj, nums[i]);
  }
  return obj;
}

void kthLargestFree(KthLargest* obj) {
  free(obj->nums);
  free(obj);
}

int main(int argc, char** argv) {
  int n, k, i, s, x;
  int* nums;
  int casecnt = 0;
  KthLargest* obj;
  while (scanf("%d", &n) != EOF) {
    printf("case %d:\n", casecnt);
    nums = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    scanf("%d", &k);
    obj = kthLargestCreate(k, nums, n);
    scanf("%d", &s);
    for (i = 0; i < s; ++i) {
      scanf("%d", &x);
      printf("kthLargestAdd: %d\n", kthLargestAdd(obj, x));
    }
    free(nums);
    free(obj);
  }
  return EXIT_SUCCESS;
}
