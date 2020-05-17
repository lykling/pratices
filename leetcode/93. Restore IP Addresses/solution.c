#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void scanValidIp(char* s, int slen, int idx, int pn, int* stack, int* rlen, char** result) {
  int n = 0;
  // printf("debug: s=%s\n", s + idx);
  // printf("debug: pn=%d\n", pn);
  // printf("debug: idx=%d\n", idx);
  // printf("debug: slen=%d\n", slen);
  // printf("debug: *rlen=%d\n", *rlen);
  if (pn >= 4) {
    if (idx == slen) {
      result[*rlen] = (char*)malloc(sizeof(char) * slen + 4);
      sprintf(result[*rlen], "%d.%d.%d.%d\0", stack[0], stack[1], stack[2], stack[3]);
      (*rlen)++;
      // printf("%d.%d.%d.%d\n", stack[0], stack[1], stack[2], stack[3]);
    }
    return;
  }
  if (idx < slen) {
    n = s[idx] - '0';
    stack[pn] = n;
    scanValidIp(s, slen, idx + 1, pn + 1, stack, rlen, result);
  }
  if (n != 0 && idx < (slen - 1)) {
    n = n * 10 + (s[idx + 1] - '0');
    stack[pn] = n;
    scanValidIp(s, slen, idx + 2, pn + 1, stack, rlen, result);
  }
  if (n != 0 && idx < (slen - 2)) {
    n = n * 10 + (s[idx + 2] - '0');
    if (n < 256) {
      stack[pn] = n;
      scanValidIp(s, slen, idx + 3, pn + 1, stack, rlen, result);
    }
  }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** restoreIpAddresses(char* s, int* returnSize) {
  int slen = strlen(s);
  // Max result size is Cmn = n!/(n-m)!m!
  // Longest valid ip is 255255255255(length==12)
  char** result = (char**)malloc(sizeof(char*) * (11 * 10 * 9) / 6);
  *returnSize = 0;
  int stack[4] = {0, 0, 0, 0};
  scanValidIp(s, slen, 0, 0, stack, returnSize, result);
  return result;
}


int main(int argc, char** argv) {
  char* s = "25525511135";
  int* returnSize = (int*)malloc(sizeof(int) * 1);
  *returnSize = 0;
  char** result = restoreIpAddresses(s, returnSize);
  int i = 0;
  for (i = 0; i < *returnSize; ++i) {
    printf("%s\n", result[i]);
  }
  printf("---\n");
  char* s2 = "010010";
  int* returnSize2 = (int*)malloc(sizeof(int) * 1);
  *returnSize2 = 0;
  char** result2 = restoreIpAddresses(s2, returnSize2);
  for (i = 0; i < *returnSize2; ++i) {
    printf("%s\n", result2[i]);
  }
  return EXIT_SUCCESS;
}
