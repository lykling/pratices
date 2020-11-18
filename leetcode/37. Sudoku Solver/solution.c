#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>

int solve(char** board, int** stack, int stacksize, int step, int* fr, int* fc, int* fm) {
  if (step == stacksize) {
    return 1;
  }
  for (int x = 0; x < 9; ++x) {
    int fg = 1 << (x + 1);
    int i = stack[step][0];
    int j = stack[step][1];
    int m = i / 3 * 3 + j / 3;
    if ((fg & fr[i]) | (fg & fc[j]) | (fg & fm[m])) {
      continue;
    }
    board[i][j] = x + '1';
    fr[i] |= fg;
    fc[j] |= fg;
    fm[m] |= fg;
    int ret = solve(board, stack, stacksize, step + 1, fr, fc, fm);
    if (ret) {
      return ret;
    }
    fr[i] &= ~fg;
    fc[j] &= ~fg;
    fm[m] &= ~fg;
    board[i][j] = '.';
  }
  return 0;
}

void solveSudoku(char** board, int boardSize, int* boardColSize){
  int** stack = (int**)malloc(sizeof(int*) * 81);
  int stacksize = 0;
  int fr[9];
  int fc[9];
  int fm[9];
  memset(fr, 0, sizeof(fr));
  memset(fc, 0, sizeof(fc));
  memset(fm, 0, sizeof(fm));
  for (int i = 0; i < boardSize; ++i) {
    for (int j = 0; j < boardColSize[i]; ++j) {
      if (board[i][j] == '.') {
        stack[stacksize] = (int*)malloc(sizeof(int) * 2);
        stack[stacksize][0] = i;
        stack[stacksize][1] = j;
        ++stacksize;
      } else {
        int fg = 1 << (board[i][j] - '0');
        int m = i / 3 * 3 + j / 3;
        fr[i] |= fg;
        fc[j] |= fg;
        fm[m] |= fg;
      }
    }
  }
  int ret = solve(board, stack, stacksize, 0, fr, fc, fm);
  for (; stacksize; free(stack[--stacksize]));
  free(stack);
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
    solveSudoku(board, 9, colsize);
    for (int j = 0; j < 9; ++j) {
      for (int k = 0; k < 9; ++k) {
        printf("%c%c", board[j][k], k == 8 ? '\n' : ' ');
      }
    }
    for (int j = 0; j < 9; ++j) {
      free(board[j]);
    }
    free(board);
  }
  return EXIT_SUCCESS;
}
