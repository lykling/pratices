#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str2int(char* x, int l, int* y) {
  *y = 0;
  int d = 1;
  while (l) {
    *y += (*(x + l-- - 1) - '0') * d;
    d *= 10;
  }
}

void int2str(int x, char* y, int d) {
  char tmp[256];
  int i = 0;
  int j = 0;
  while (x > 0) {
    tmp[i++] = x % 10 + '0';
    x /= 10;
  }
  for (j = 0; j < d - i; ++j, ++y) {
    *y = '0';
  }
  for (j = 0; j < i; ++ j) {
    y[j] = tmp[i - j - 1];
  }
  y[j] = '\0';
}

char* plus(char* x, char* y) {
}

char* multiply(char* x, char* y) {
  int xl = strlen(x);
  int yl = strlen(y);
  int d = 6;
  int dd = 1000000;
  int xs = (xl + d - 1) / d;
  int ys = (yl + d - 1) / d;
  int i = 0;
  int j = 0;
  int tmp[xs + ys];
  int xi;
  int yi;
  int l;
  int r;
  int m;
  int mm;
  char* p = malloc(sizeof(char) * (xl + yl + 1));
  char* pp = p;
  char* tp;
  int k;
  memset(tmp, 0, sizeof(int) * (xs + ys));
  for (i = 0; i < xs; ++i) {
    for (j = 0; j < ys; ++j) {
      xi = xl - (i * d) - d;
      yi = yl - (j * d) - d;
      (xi < 0) ? str2int(x, xl % d, &l) : str2int(x + xi, d, &l);
      (yi < 0) ? str2int(y, yl % d, &r) : str2int(y + yi, d, &r);
      m = l * r;
      mm = m + tmp[i + j];
      printf("i:%d, j:%d, l:%d, r:%d, m:%d, mm: %d", i, j, l, r, m, mm);
      for (k = 0; k < xl + yl; ++k) {
        printf("%d%c", tmp[k], k == xl + yl - 1 ? '\n' : ' ');
      }
      tmp[i + j] = mm % dd;
      tmp[i + j + 1] += mm / dd;
      for (k = 0; k < xl + yl; ++k) {
        printf("%d%c", tmp[k], k == xl + yl - 1 ? '\n' : ' ');
      }
    }
  }
  i = xs + ys - 1;
  while (i > 0 && tmp[i] == 0) {
    --i;
  }
  tp = malloc(sizeof(char) * (d + 1));
  for (j = i; j >= 0; --j) {
    j == i ? int2str(tmp[j], tp, 1) : int2str(tmp[j], tp, d);
    strcpy(pp, tp);
    pp += strlen(tp);
  }
  free(tp);
  return p;
}

int main(int argc, char** argv) {
  char* x = "123";
  char* y = "456";
  printf("%s * %s = %s\n", x, y, multiply(x, y));
  x = "12455234";
  y = "24362783886";
  printf("%s * %s = %s\n", x, y, multiply(x, y));
  x = "100000002";
  y = "256";
  printf("%s * %s = %s\n", x, y, multiply(x, y));
  x = "0";
  y = "0";
  printf("%s * %s = %s\n", x, y, multiply(x, y));
  return EXIT_SUCCESS;
}
