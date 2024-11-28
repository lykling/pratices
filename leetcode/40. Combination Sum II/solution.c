#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int intCmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int intCmpR(const void *a, const void *b) { return *(int *)b - *(int *)a; }

void iqsort(void *arr, int size, int len,
            int (*cmp)(const void *, const void *)) {
  int l = 0;
  int r = len - 1;
  int m = (l + r) / 2;
  void *e_m = (void *)malloc(size);
  memcpy(e_m, arr + m * size, size);
  void *tmp = malloc(size);
  for (; l <= r && l < len && r >= 0;) {
    for (; l <= r && cmp(arr + l * size, e_m) < 0; ++l) {
    }
    for (; r >= 0 && cmp(arr + r * size, e_m) > 0; --r) {
    }
    if (l <= r) {
      memcpy(tmp, arr + l * size, size);
      memcpy(arr + l * size, arr + r * size, size);
      memcpy(arr + r * size, tmp, size);
      ++l;
      --r;
    }
  }
  free(tmp);
  free(e_m);
  if (l < len - 1) {
    iqsort(arr + l * size, size, len - l, cmp);
  }
  if (r > 0) {
    iqsort(arr, size, r + 1, cmp);
  }
}

void find_combinations(int target, int *candidates, int candidatesSize,
                       int *stack, int depth, int offset, int **result,
                       int *returnSize, int **returnColumnSizes) {

  if (target == 0) {
    result[*returnSize] = (int *)malloc(sizeof(int) * 40);
    for (int i = 0; i < depth; ++i) {
      result[*returnSize][i] = stack[i];
    }
    (*returnColumnSizes)[*returnSize] = depth;
    (*returnSize)++;
    return;
  }

  for (int i = offset; i < candidatesSize; ++i) {
    // printf("  offset: %d, i: %d, candidates[i]: %d\n", offset, i,
    //        candidates[i]);
    if (i - offset > 0 && candidates[i] == candidates[i - 1]) {
      continue;
    }
    if (candidates[i] <= target) {
      stack[depth] = candidates[i];
      find_combinations(target - candidates[i], candidates, candidatesSize,
                        stack, depth + 1, i + 1, result, returnSize,
                        returnColumnSizes);
    }
  }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **combinationSum2(int *candidates, int candidatesSize, int target,
                      int *returnSize, int **returnColumnSizes) {
  int **result = (int **)malloc(sizeof(int *) * 1000);
  returnColumnSizes[0] = (int *)malloc(sizeof(int) * 1000);
  *returnSize = 0;
  int stack[100];

  iqsort(candidates, sizeof(int), candidatesSize, intCmpR);

  find_combinations(target, candidates, candidatesSize, stack, 0, 0, result,
                    returnSize, returnColumnSizes);

  return result;
}

int main() {
  int case_n;
  scanf("%d", &case_n);
  for (int i = 0; i < case_n; ++i) {
    int candidates_size;
    scanf("%d", &candidates_size);
    int *candidates = (int *)malloc(sizeof(int) * candidates_size);
    for (int j = 0; j < candidates_size; ++j) {
      scanf("%d", &candidates[j]);
    }
    int target;
    scanf("%d", &target);

    int returnSize = 0;
    // int *returnColumnSizes = (int *)malloc(sizeof(int) * 1000);
    int *returnColumnSizes;
    int **result = combinationSum2(candidates, candidates_size, target,
                                   &returnSize, &returnColumnSizes);

    printf("case[%d]: result size: %d\n", i, returnSize);
    for (int j = 0; j < returnSize; ++j) {
      printf("  result[%d]: [", j);
      for (int k = 0; k < returnColumnSizes[j]; ++k) {
        printf("%d, ", result[j][k]);
      }
      printf("]\n");
    }

    for (int j = 0; j < returnSize; ++j) {
      free(result[j]);
    }
    free(result);
    free(returnColumnSizes);
    free(candidates);
  }
  return 0;
}
