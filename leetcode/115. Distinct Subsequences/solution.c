#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSubSeq(char* s, int slen, char* t, int tlen, int m, int n, int cache[m][n]) {
  if (slen < 0 || tlen < 0) {
    return 0;
  }
  if (slen < tlen) {
    return 0;
  }
  if (tlen == 0) {
    return 1;
  }
  if (cache[slen][tlen] != -1) {
    return cache[slen][tlen];
  }
  int cnt = 0;
  cnt = countSubSeq(s + 1, slen - 1, t, tlen, m, n, cache);
  if (s[0] == t[0]) {
    cnt += countSubSeq(s + 1, slen - 1, t + 1, tlen - 1, m, n, cache);
  }
  cache[slen][tlen] = cnt;
  return cnt;
}

int numDistinct(char* s, char* t) {
  int slen = strlen(s);
  int tlen = strlen(t);
  int cache[slen+1][tlen+1];
  memset(cache, -1, sizeof(int) * (slen + 1) * (tlen + 1));
  return countSubSeq(s, slen, t, tlen, slen + 1, tlen + 1, cache);
}

int main(int argc, char** argv) {
  char* s1 = "rabbbit";
  char* t1 = "rabbit";
  printf("cnt1: %d\n", numDistinct(s1, t1));

  char* s2 = "babgbag";
  char* t2 = "bag";
  printf("cnt2: %d\n", numDistinct(s2, t2));
}
