#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>

void printBits(int n) {
  char bits[256];
  int c = 0;
  while (n) {
    bits[c++] = (n % 2) + '0';
    n /= 2;
  }
  for (int i = c - 1; i >= 0; --i) {
    printf("%c", bits[i]);
  }
  printf("\n");
}

bool isValidSudoku(char** board, int boardSize, int* boardColSize){
  int fr[9];
  int fc[9];
  int fm[9];
  memset(fr, 0, sizeof(fr));
  memset(fc, 0, sizeof(fc));
  memset(fm, 0, sizeof(fm));
  for (int i = 0; i < boardSize; ++i) {
    for (int j = 0; j < boardColSize[i]; ++j) {
      if (board[i][j] == '.') {
        continue;
      }
      int fg = 1 << (board[i][j] - '0');
      int m = i / 3 * 3 + j / 3;
      // printf("i: %d, j: %d, m: %d\n", i, j, m);
      // printf("board[i][j]: %c\n", board[i][j]);
      // printf("fg:");
      // printBits(fg);
      // printf("fr:");
      // printBits(fr[i]);
      // printf("fc:");
      // printBits(fc[j]);
      // printf("fm:");
      // printBits(fm[m]);
      if (fr[i] & fg) {
        return false;
      }
      if (fc[j] & fg) {
        return false;
      }
      if (fm[m] & fg) {
        return false;
      }
      fr[i] |= fg;
      fc[j] |= fg;
      fm[m] |= fg;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    char** board = (char**)malloc(sizeof(char*) * 9);
    for (int j = 0; j < 9; ++j) {
      board[j] = (char*)malloc(sizeof(char) * 9);
      scanf("%s", board[j]);
      // for (int k = 0; k < 9; ++k) {
      //   scanf("%c", board[j] + k);
      // }
    }
    for (int j = 0; j < 9; ++j) {
      for (int k = 0; k < 9; ++k) {
        printf("%c%c", board[j][k], k == 8 ? '\n' : ' ');
      }
    }
    int colsize[9] = {9, 9, 9, 9, 9, 9, 9, 9, 9};
    printf("isValidSudoku: %d\n", isValidSudoku(board, 9, colsize));
    for (int j = 0; j < 9; ++j) {
      free(board[j]);
    }
    free(board);
  }
  return EXIT_SUCCESS;
}
