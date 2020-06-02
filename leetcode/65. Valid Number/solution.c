#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>

bool isNumber(char* s){
  int s_n = 0;
  int s_e = 0;
  int f_n = 0;
  int f_e = 0;
  int f_d = 0;
  int f_x = 0;
  int n = strlen(s);
  int i = 0;
  while (n > 0 && s[0] == ' ') {
    ++s;
    --n;
  }
  while (n > 0 && s[n - 1] == ' ') {
    --n;
  }
  for (i = 0; i < n; ++i) {
    switch (s[i]) {
      case '+':
      case '-':
        if (s_e != 0) {
          return false;
        }
        if (f_x == 1) {
          if (f_e) {
            return false;
          }
          s_e = 1;
          continue;
        }
        if (s_n != 0) {
          return false;
        }
        if (f_n) {
          return false;
        }
        if (f_d) {
          return false;
        }
        s_n = 1;
        break;
      case '.':
        if (f_d != 0) {
          return false;
        }
        if (f_x != 0) {
          return false;
        }
        f_d = 1;
        break;
      case 'e':
        if (f_x != 0) {
          return false;
        }
        f_x = 1;
        break;
      case ' ':
        return false;
      default:
        if (s[i] < '0' || s[i] > '9') {
          return false;
        }
        if (f_x) {
          f_e = 1;
        } else {
          f_n = 1;
        }
        break;
    }
  }
  if (f_n == 0) {
    return false;
  }
  if (f_x != 0 && f_e == 0) {
    return false;
  }
  return true;
}

int main(int argc, char** argv) {
  char* ss[] = {
    "0",
    " 0.1",
    "abc",
    "1 a",
    "2e10",
    " -90e3   ",
    " 1e",
    "e3",
    " 6e-1",
    " 99e2.5 ",
    "53.5e93",
    " --6 ",
    "-+3",
    "95a54e53",
    "6+1",
    ".-4",
    ".1"
  };
  int n = 17;
  int i = 0;
  for (i = 0; i < n; ++i) {
    printf("`%s`\t=>\t%s\n", ss[i], isNumber(ss[i]) ? "true" : "false");
  }
}
