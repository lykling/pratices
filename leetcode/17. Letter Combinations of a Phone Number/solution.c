#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_combinations(char *digits, int len, char *stack, int depth,
                       int *digit_letter_offset_map, char **result,
                       int *returnSize) {
  if (depth == len) {
    result[*returnSize] = (char *)malloc(sizeof(char) * (len + 1));
    memcpy(result[*returnSize], stack, len);
    result[*returnSize][len] = '\0';
    (*returnSize)++;
    return;
  }

  int digit = digits[depth] - '0' - 2;
  int start = digit_letter_offset_map[digit];
  int end = digit_letter_offset_map[digit + 1];
  for (int i = start; i < end; ++i) {
    stack[depth] = 'a' + i;
    find_combinations(digits, len, stack, depth + 1, digit_letter_offset_map,
                      result, returnSize);
  }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCombinations(char *digits, int *returnSize) {

  int digit_letter_offset_map[] = {0, 3, 6, 9, 12, 15, 19, 22, 26};
  // int *digit_letter_offset_map = (int *)malloc(sizeof(int) * 10);
  // digit_letter_offset_map[0] = 0;
  // digit_letter_offset_map[1] = 3;
  // digit_letter_offset_map[2] = 6;
  // digit_letter_offset_map[3] = 9;
  // digit_letter_offset_map[4] = 12;
  // digit_letter_offset_map[5] = 15;
  // digit_letter_offset_map[6] = 19;
  // digit_letter_offset_map[7] = 22;
  int len = strlen(digits);
  *returnSize = 0;
  if (len == 0) {
    return NULL;
  }
  char **result = (char **)malloc(sizeof(char *) * 256);

  char *stack = (char *)malloc(sizeof(char) * len);
  find_combinations(digits, len, stack, 0, digit_letter_offset_map, result,
                    returnSize);

  free(stack);
  // free(digit_letter_offset_map);

  return result;
}

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  int case_n = 0;
  scanf("%d\n", &case_n);

  for (int i = 0; i < case_n; ++i) {
    char digits[1024];
    scanf("%[^\n]\n", digits);

    int returnSize = 0;
    char **result = letterCombinations(digits, &returnSize);

    printf("case[%d]: digits: %s, result size: %d\n", i, digits, returnSize);
    for (int j = 0; j < returnSize; ++j) {
      printf("%s\n", result[j]);
      free(result[j]);
    }
    free(result);
  }
  return 0;
}
