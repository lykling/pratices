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
  struct TreeNode *left;
  struct TreeNode *right;
};

bool isMirror(struct TreeNode* left, struct TreeNode* right) {
  if (left == NULL || right == NULL) {
    return left == right;
  }
  if (left->val != right->val) {
    return false;
  }
  return isMirror(left->left, right->right) && isMirror(left->right, right->left);
}

bool isSymmetric(struct TreeNode* root){
  if (root == NULL) {
    return true;
  }
  return isMirror(root->left, root->right);
}

void ldr(struct TreeNode* root) {
  if (root != NULL) {
    ldr(root->left);
    printf("%d ", root->val);
    ldr(root->right);
  }
}

void dlr(struct TreeNode* root) {
  if (root != NULL) {
    printf("%d ", root->val);
    dlr(root->left);
    dlr(root->right);
  }
}

void lrd(struct TreeNode* root) {
  if (root != NULL) {
    lrd(root->left);
    lrd(root->right);
    printf("%d ", root->val);
  }
}

int main(int argc, char** argv) {
  int i;
  int arr[] = {1,2,2,3,4,4,3};
  struct TreeNode** tnl = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 7);
  for (i = 0; i < 7; ++i) {
    tnl[i] = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    tnl[i]->val = arr[i];
    if (i > 0) {
      if (i % 2) {
        tnl[(i - 1) / 2]->left = tnl[i];
      } else {
        tnl[(i - 1) / 2]->right = tnl[i];
      }
    }
  }
  dlr(tnl[0]);
  printf("\n");
  ldr(tnl[0]);
  printf("\n");
  lrd(tnl[0]);
  printf("\n");
  printf("isSymmetric: %d\n", isSymmetric(tnl[0]));
}
