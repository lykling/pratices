#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>

typedef struct {
  int idx;
  int freq;
  int pos;
} HeapNode;

struct ITreeNode {
  int idx;
  HeapNode* node;
  struct ITreeNode* left;
  struct ITreeNode* right;
};

void swap(HeapNode** heap, int a, int b) {
  HeapNode* tmp = heap[a];
  heap[a] = heap[b];
  heap[a]->pos = a;
  heap[b] = tmp;
  heap[b]->pos = b;
}

void swim(HeapNode** heap, int p) {
  while (p) {
    int pp = (p - 1) / 2;
    if (heap[p]->freq < heap[pp]->freq) {
      swap(heap, pp, p);
    }
    p = pp;
  }
}

void sink(HeapNode** heap, int p, int n) {
  int l = (p + 1) * 2 - 1;
  int r = l + 1;
  while (l < n || r < n) {
    if (r >= n) {
      if (heap[p]->freq > heap[l]->freq) {
        swap(heap, p, l);
        p = l;
      } else {
        break;
      }
    } else if (heap[l]->freq <= heap[r]->freq) {
      if (heap[p]->freq > heap[l]->freq) {
        swap(heap, p, l);
        p = l;
      } else {
        break;
      }
    } else {
      if (heap[p]->freq > heap[r]->freq) {
        swap(heap, p, r);
        p = r;
      } else {
        break;
      }
    }
    l = (p + 1) * 2 - 1;
    r = l + 1;
  }
}

struct ITreeNode* treeCreate(int idx) {
  struct ITreeNode* node = (struct ITreeNode*)malloc(sizeof(struct ITreeNode));
  node->idx = idx;
  node->node = (HeapNode*)malloc(sizeof(HeapNode));
  node->node->idx = idx;
  node->node->freq = 0;
  node->node->pos = -1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

struct ITreeNode* treeFindOrCreate(struct ITreeNode* root, int idx) {
  if (root == NULL) {
    return treeCreate(idx);
  }
  if (idx < root->idx) {
    if (root->left) {
      return treeFindOrCreate(root->left, idx);
    } else {
      root->left = treeCreate(idx);
      return root->left;
    }
  } else if (idx > root->idx) {
    if (root->right) {
      return treeFindOrCreate(root->right, idx);
    } else {
      root->right = treeCreate(idx);
      return root->right;
    }
  }
  return root;
}

void treeFree(struct ITreeNode* root) {
  if (root->left) {
    treeFree(root->left);
    root->left = NULL;
  }
  if (root->right) {
    treeFree(root->right);
    root->right = NULL;
  }
  free(root->node);
  root->node = NULL;
  free(root);
}

void treePrint(struct ITreeNode* tree) {
  if (tree == NULL) {
    return;
  }
  treePrint(tree->left);
  printf("tree: %d\n", tree->idx);
  treePrint(tree->right);
}

int* topKFrequent(int* nums, int n, int k, int* retn) {
  int i;
  int p;
  HeapNode** heap = (HeapNode**)malloc(sizeof(HeapNode*) * k);
  struct ITreeNode* tp;
  struct ITreeNode* tree = treeFindOrCreate(NULL, nums[0]);
  tree->node->freq = 1;
  tree->node->pos = 0;
  heap[0] = tree->node;
  p = 1;
  // treePrint(tree);
  for (i = 1; i < n; ++i) {
    tp = treeFindOrCreate(tree, nums[i]);
    // printf("----\n");
    // printf("p: %d, k: %d, n: %d\n", p, k, n);
    // treePrint(tree);
    // printf("tp->idx: %d, tp->node->freq: %d\n", tp->idx, tp->node->freq);
    // printf("----\n");
    tp->node->freq += 1;
    // existed node
    if (tp->node->freq > 1) {
      if (tp->node->pos != -1) {
        sink(heap, tp->node->pos, p);
      } else {
        if (tp->node->freq > heap[0]->freq) {
          heap[0]->pos = -1;
          heap[0] = tp->node;
          tp->node->pos = 0;
          sink(heap, 0, p);
        }
      }
    } else {
      if (p < k) {
        // printf("add to heap and swim, %d, %d\n", tp->idx, p);
        tp->node->pos = p;
        heap[p] = tp->node;
        swim(heap, p++);
        // printf("add to heap and swim done, %d, %d\n", tp->idx, p);
      } else {
        if (tp->node->freq > heap[0]->freq) {
          heap[0]->pos = -1;
          heap[0] = tp->node;
          tp->node->pos = 0;
          sink(heap, 0, p);
        }
      }
    }
  }
  int* ret = (int*)malloc(sizeof(int) * k);
  for (i = 0; i < k; ++i) {
    ret[i] = heap[i]->idx;
  }
  treeFree(tree);
  free(heap);
  *retn = k;
  return ret;
}

int main(int argc, char** argv) {
  int n, k, retn, i;
  int* nums;
  int* ret;
  while (scanf("%d", &n) != EOF) {
    nums = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    scanf("%d", &k);
    ret = topKFrequent(nums, n, k, &retn);
    for (i = 0; i < retn; ++i) {
      printf("%d%c", ret[i], i == retn - 1 ? '\n' : ' ');
    }
    free(nums);
  }
  return EXIT_SUCCESS;
}
