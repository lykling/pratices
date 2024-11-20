#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wordCmp(const void *a, const void *b) {
  char *aa = *((char **)a);
  char *bb = *((char **)b);
  int len = strlen(bb);
  for (int i = 0; i < len; ++i) {
    if (aa[i] == bb[i]) {
      continue;
    }
    return aa[i] - bb[i];
  }
  return 0;
}

void iqsort(void *arr, int size, int len,
            int (*cmp)(const void *, const void *)) {
  int l = 0;
  int r = len - 1;
  int m = (l + r) / 2;
  const void *e_m = arr + m * size;
  // printf("l: %d r: %d m: %d\n", l, r, m);
  for (; l < r && l < len && r >= 0;) {
    for (; l <= r && cmp(arr + l * size, e_m) < 0; ++l) {
    }
    for (; r >= 0 && cmp(arr + r * size, e_m) > 0; --r) {
    }
    if (l <= r) {
      void *tmp = malloc(size);
      memcpy(tmp, arr + l * size, size);
      memcpy(arr + l * size, arr + r * size, size);
      memcpy(arr + r * size, tmp, size);
      free(tmp);
      ++l;
      --r;
    }
  }
  if (l < len - 1) {
    iqsort(arr + l * size, size, len - l, cmp);
  }
  if (r > 0) {
    iqsort(arr, size, r + 1, cmp);
  }
}

int matchSum(int *idxs, int cnt, int step, int *multiple) {
  // printf("cnt: %d step: %d\n", cnt, step);
  int sum = 0;
  int flag[5001];
  memset(flag, 0, sizeof(flag));

  int tmp;
  for (int i = 0; i < cnt; ++i) {
    tmp = idxs[i * step];
    if (tmp < 0) {
      sum += tmp;
      return sum;
    } else {
      sum += tmp + (flag[tmp]++ % multiple[tmp]);
    }
  }
  return sum;
}

int intCmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int *findSubstring(char *s, char **words, int wordsSize, int *returnSize) {
  if (wordsSize == 0) {
    *returnSize = 0;
    return NULL;
  }
  int s_len = strlen(s);
  int word_len = strlen(words[0]);
  // printf("s_len: %d word_len: %d\n", s_len, word_len);
  iqsort(words, sizeof(char *), wordsSize, wordCmp);

  int *multiple = (int *)malloc(sizeof(int) * wordsSize);
  for (int i = 0, last = 0; i < wordsSize; ++i) {
    if (i == 0) {
      multiple[i] = 1;
      continue;
    }

    if (wordCmp(words + i, words + i - 1) == 0) {
      multiple[i] = multiple[i - 1] + 1;
      for (int j = last; j < i; ++j) {
        multiple[j] = multiple[i];
      }
    } else {
      multiple[i] = 1;
      last = i;
    }
  }
  // for (int i = 0; i < wordsSize; ++i) {
  //   printf("%d ", multiple[i]);
  // }
  // printf("\n");

  int *idxs = (int *)malloc(sizeof(int) * s_len);
  for (int i = 0; i < s_len; ++i) {
    idxs[i] = -1;
    char *ss = s + i;
    for (int j = 0; j < wordsSize; ++j) {
      if (wordCmp(&ss, words + j) == 0) {
        idxs[i] = j;
        break;
      }
    }
  }
  // for (int i = 0; i < s_len; ++i) {
  //   printf("%d ", idxs[i]);
  // }
  // printf("\n");

  int *result = (int *)malloc(sizeof(int) * s_len);
  int result_size = 0;
  int match_num = (wordsSize - 1) * wordsSize / 2;
  // printf("match_num: %d\n", match_num);
  for (int i = 0; i < s_len; ++i) {
    if (i + wordsSize * word_len > s_len) {
      break;
    }
    int match_sum = matchSum(idxs + i, wordsSize, word_len, multiple);
    // printf("i: %d match_sum: %d\n", i, match_sum);
    if (match_sum == match_num) {
      result[result_size++] = i;
    }
  }

  free(idxs);
  free(multiple);

  *returnSize = result_size;
  return result;
}

int main(int argc, char **argv) {

  // int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  // iqsort(a, sizeof(int), 9, intCmp);
  // for (int i = 0; i < 9; ++i) {
  //   printf("%d ", a[i]);
  // }
  // printf("\n");

  char *b[] = {"word\0", "good\0", "best\0", "good\0"};
  iqsort(b, sizeof(char *), 4, wordCmp);
  for (int i = 0; i < 4; ++i) {
    printf("%s ", b[i]);
  }
  printf("\n");

  int case_num;
  scanf("%d", &case_num);
  for (int i = 0; i < case_num; ++i) {
    char s[1000];
    scanf("%s", s);
    int words_size;
    scanf("%d", &words_size);
    char **words = (char **)malloc(sizeof(char *) * words_size);
    for (int j = 0; j < words_size; ++j) {
      words[j] = (char *)malloc(sizeof(char) * 100);
      scanf("%s", words[j]);
    }
    // if (words_size > 0) {
    //   int word_len = strlen(words[0]);
    //   for (int j = 0; j < words_size; ++j) {
    //     for (int k = 0; k < word_len; ++k) {
    //       printf("%c", words[j][k]);
    //     }
    //     printf(" ");
    //   }
    //   printf("\n");
    //   iqsort(words, sizeof(char *), words_size, wordCmp);
    //   for (int j = 0; j < words_size; ++j) {
    //     for (int k = 0; k < word_len; ++k) {
    //       printf("%c", words[j][k]);
    //     }
    //     printf(" ");
    //   }
    //   printf("\n");
    // }

    int result_size;
    int *result = findSubstring(s, words, words_size, &result_size);
    printf("case[%d]: ", i);
    printf("result_size: %d\n", result_size);
    for (int j = 0; j < result_size; ++j) {
      printf("%d ", result[j]);
    }
    printf("\n");
    free(result);

    for (int j = 0; j < words_size; ++j) {
      free(words[j]);
    }
    free(words);
  }
  return EXIT_SUCCESS;
}
