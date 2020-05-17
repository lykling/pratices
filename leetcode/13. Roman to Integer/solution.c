#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int romanToInt(char * s){
  int len = strlen(s);
  int* sym = (int*)malloc(sizeof(int) * 26);
  char* p = s;
  int sum = 0;
  int l;
  int r;
  int d;

  if (len <= 0) {
    return 0;
  }

  memset(sym, 0, sizeof(int) * 26);
  sym['I' - 'A'] = 1;
  sym['V' - 'A'] = 5;
  sym['X' - 'A'] = 10;
  sym['L' - 'A'] = 50;
  sym['C' - 'A'] = 100;
  sym['D' - 'A'] = 500;
  sym['M' - 'A'] = 1000;

  sum = sym[*(p++) - 'A'];
  while (*p != '\0') {
    l = sym[*(p - 1) - 'A'];
    r = sym[*p - 'A'];
    d = r / l;
    if (d == 5 || d == 10) {
      sum -= l;
      sum += r - l;
    } else {
      sum += r;
    }
    ++p;
  }
  return sum;
}

int main(int argc, char** argv) {
  printf("roman: MCMXCIV, int: %d\n", romanToInt("MCMXCIV"));
  printf("roman: LVIII, int: %d\n", romanToInt("LVIII"));
  printf("roman: IX, int: %d\n", romanToInt("IX"));
  printf("roman: IV, int: %d\n", romanToInt("IV"));
  printf("roman: III, int: %d\n", romanToInt("III"));
  return EXIT_SUCCESS;
}
