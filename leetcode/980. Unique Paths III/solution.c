#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>

void walk(int** grid, int gridSize, int* gridColSize, int x, int y, int step, int maxStep, int* result) {
  int dirs[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
  for (int i = 0; i < 4; ++i) {
    int xx = x + dirs[i][0];
    int yy = y + dirs[i][1];
    if (xx < 0 || xx >= gridSize) {
      continue;
    }
    if (yy < 0 || yy >= gridColSize[xx]) {
      continue;
    }
    int cc = grid[xx][yy];
    if (cc == -1 || cc == 1) {
      continue;
    }
    if (cc == 2) {
      if (maxStep - step == 0) {
        *result += 1;
        return;
      } else {
        continue;
      }
    }
    // cc == 0
    grid[xx][yy] = -1;
    walk(grid, gridSize, gridColSize, xx, yy, step + 1, maxStep, result);
    grid[xx][yy] = cc;
  }
}

int uniquePathsIII(int** grid, int gridSize, int* gridColSize){
  int maxStep = 0;
  int x = 0;
  int y = 0;
  for (int i = 0; i < gridSize; ++i) {
    for (int j = 0; j < gridColSize[i]; ++j) {
      if (grid[i][j] == 1) {
        x = i;
        y = j;
      } else if (grid[i][j] == 0) {
        ++maxStep;
      }
    }
  }
  int result = 0;
  walk(grid, gridSize, gridColSize, x, y, 0, maxStep, &result);
  return result;
}

int main(int argc, char** argv) {
  int** grid;
  for (int m, n; scanf("%d %d", &m, &n) != EOF;) {
    grid = (int**)malloc(sizeof(int*) * m);
    for (int i = 0; i < m; ++i) {
      grid[i] = (int*)malloc(sizeof(int) * n);
      for (int j = 0; j < n; ++j) {
        scanf("%d", grid[i] + j);
      }
    }
    int* colsize = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; ++i) {
      colsize[i] = n;
    }
    printf("uniquePathsIII: %d\n", uniquePathsIII(grid, m, colsize));

    free(colsize);
    for (int i = 0; i < m; ++i) {
      free(grid[i]);
    }
    free(grid);
  }
}
