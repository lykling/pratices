#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
};

int getTreeDepth(struct TreeNode* root) {
  if (root == NULL) {
    return 0;
  }
  int left = getTreeDepth(root->left);
  int right = getTreeDepth(root->right);
  if (left > right) {
    return left + 1;
  }
  return right + 1;
}


bool isBalanced(struct TreeNode* root) {
  if (root == NULL) {
    return true;
  }
  /* printf("balance: %d\n", root->val); */
  if (!isBalanced(root->left) || !isBalanced(root->right)) {
    return false;
  }
  int dl = getTreeDepth(root->left);
  int dr = getTreeDepth(root->right);
  /* printf("dr: %d, dl: %d\n", dr, dl); */
  if (abs(dl - dr) <= 1) {
    return true;
  }
  return false;
}

void buildTree(int* arr, int len, struct TreeNode** nodes) {
  int i = 0;
  for (i = 0; i < len; ++i) {
    printf("build: arr[%d]\n", i);
    printf("build: arr[%d]=%d\n", i, arr[i]);
    if (arr[i] != -1) {
      nodes[i] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
      nodes[i]->val = arr[i];
      nodes[i]->left = NULL;
      nodes[i]->right = NULL;
      if (i > 0) {
        if (i % 2) {
          nodes[(i - 1) / 2]->left = nodes[i];
        } else {
          nodes[(i - 1) / 2]->right = nodes[i];
        }
      }
    } else {
      nodes[i] = NULL;
    }
  }
  printf("build done\n");
}

void freeTree(struct TreeNode** nodes, int len) {
  int i = 0;
  for (i = 0; i < len; ++i) {
    free(nodes[i]);
  }
  free(nodes);
}

int main(int argc, char** argv) {
  int i = 0;
  int n = 7;
  int a[] = {3, 9, 20, -1, -1, 15, 7};
  struct TreeNode** nodes = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * n);
  buildTree(a, n, nodes);
  for (i = 0; i < n; ++i) {
    printf("nodes[%d]->val = %d\n", i, nodes[i] == NULL ? -1 : nodes[i]->val);
  }
  printf("test1: %d\n", isBalanced(nodes[0]));
  freeTree(nodes, n);

  printf("-------\n");
  n = 9;
  int b[] = {1, 2, 2, 3, 3, -1, -1, 4, 4};
  nodes = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * n);
  buildTree(b, n, nodes);
  for (i = 0; i < n; ++i) {
    printf("nodes[%d]->val = %d\n", i, nodes[i] == NULL ? -1 : nodes[i]->val);
  }
  printf("test2: %d\n", isBalanced(nodes[0]));
  return EXIT_SUCCESS;
}
