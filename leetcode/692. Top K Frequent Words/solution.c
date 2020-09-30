#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
  char* idx;
  int freq;
  int pos;
} HeapNode;

struct ITreeNode {
  char* idx;
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

int heapCmp(HeapNode* a, HeapNode* b) {
  if (a->freq > b->freq) {
    return -1;
  } else if (a->freq < b->freq) {
    return 1;
  } else {
    return strcmp(a->idx, b->idx);
  }
}

void swim(HeapNode** heap, int p) {
  while (p) {
    int pp = (p - 1) / 2;
    if (heapCmp(heap[p], heap[pp]) > 0) {
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
      if (heapCmp(heap[p], heap[l]) < 0) {
        swap(heap, p, l);
        p = l;
      } else {
        break;
      }
    } else if (heapCmp(heap[l], heap[r]) >= 0) {
      if (heapCmp(heap[p], heap[l]) < 0) {
        swap(heap, p, l);
        p = l;
      } else {
        break;
      }
    } else {
      if (heapCmp(heap[p], heap[r]) < 0) {
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

void heapSort(HeapNode** heap, int l, int r) {
  int m = (r - l) / 2 + l;
  HeapNode* mm = heap[m];
  int ll = l;
  int rr = r;
  while (ll < rr) {
    for (;heapCmp(heap[ll], mm) < 0; ++ll);
    for (;heapCmp(heap[rr], mm) > 0; --rr);
    if (ll < rr) {
      swap(heap, ll, rr);
    }
  }
  if (l < rr) {
    heapSort(heap, l, rr - 1);
  }
  if (r > ll) {
    heapSort(heap, ll + 1, r);
  }
}

struct ITreeNode* treeCreate(char* idx) {
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

struct ITreeNode* treeFindOrCreate(struct ITreeNode* root, char* idx) {
  if (root == NULL) {
    return treeCreate(idx);
  }
  int cmp = strcmp(idx, root->idx);
  if (cmp < 0) {
    if (root->left) {
      return treeFindOrCreate(root->left, idx);
    } else {
      root->left = treeCreate(idx);
      return root->left;
    }
  } else if (cmp > 0) {
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

char** topKFrequent(char** words, int n, int k, int* retn) {
  int i;
  int p;
  HeapNode** heap = (HeapNode**)malloc(sizeof(HeapNode*) * k);
  struct ITreeNode* tp;
  struct ITreeNode* tree = treeFindOrCreate(NULL, words[0]);
  tree->node->freq = 1;
  tree->node->pos = 0;
  heap[0] = tree->node;
  p = 1;
  for (i = 1; i < n; ++i) {
    tp = treeFindOrCreate(tree, words[i]);
    tp->node->freq += 1;
    // existed node
    if (tp->node->freq > 1) {
      if (tp->node->pos != -1) {
        sink(heap, tp->node->pos, p);
      } else {
        if (heapCmp(tp->node, heap[0]) < 0) {
          heap[0]->pos = -1;
          heap[0] = tp->node;
          tp->node->pos = 0;
          sink(heap, 0, p);
        }
      }
    } else {
      if (p < k) {
        tp->node->pos = p;
        heap[p] = tp->node;
        swim(heap, p++);
      } else {
        if (heapCmp(tp->node, heap[0]) < 0) {
          heap[0]->pos = -1;
          heap[0] = tp->node;
          tp->node->pos = 0;
          sink(heap, 0, p);
        }
      }
    }
  }
  heapSort(heap, 0, k - 1);
  char** ret = (char**)malloc(sizeof(char*) * k);
  for (i = 0; i < k; ++i) {
    ret[i] = heap[i]->idx;
  }
  treeFree(tree);
  free(heap);
  *retn = k;
  return ret;
}

void treePrint(struct ITreeNode* tree) {
  if (tree == NULL) {
    return;
  }
  treePrint(tree->left);
  printf("tree: %s\n", tree->idx);
  treePrint(tree->right);
}

int main(int argc, char** argv) {
  int n, k, retn, i;
  char** words;
  char** ret;
  while (scanf("%d", &n) != EOF) {
    words = (char**)malloc(sizeof(char*) * n);
    for (i = 0; i < n; ++i) {
      words[i] = (char*)malloc(sizeof(char) * 32);
      scanf("%s", words[i]);
    }
    scanf("%d", &k);
    ret = topKFrequent(words, n, k, &retn);
    for (i = 0; i < retn; ++i) {
      printf("%s%c", ret[i], i == retn - 1 ? '\n' : ' ');
    }
    free(ret);
    for (i = 0; i < n; ++i) {
      free(words[i]);
    }
    free(words);
  }
  return EXIT_SUCCESS;
}
