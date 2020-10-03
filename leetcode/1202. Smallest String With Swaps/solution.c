#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <memory.h>
#include <string.h>

struct ITree {
  int p;
  char c;
  int s;
  int w;
  struct ITree* left;
  struct ITree* right;
};

void treeSwapChar(struct ITree* a, struct ITree* b) {
  char c = a->c;
  a->c = b->c;
  b->c = c;
}

void treeQuickSort(struct ITree** nodes, int l, int r) {
  int m = (r - l) / 2 + l;
  int ll = l;
  int rr = r;
  char mc = nodes[m]->c;
  for (; ll < rr;) {
    for (; nodes[ll]->c < mc; ++ll);
    for (; nodes[rr]->c > mc; --rr);
    if (ll <= rr) {
      treeSwapChar(nodes[ll++], nodes[rr--]);
    }
  }
  if (ll < r) {
    treeQuickSort(nodes, ll, r);
  }
  if (rr > l) {
    treeQuickSort(nodes, l, rr);
  }
}

struct ITree* treeCreate(int p, char c) {
  struct ITree* tree = (struct ITree*)malloc(sizeof(struct ITree));
  tree->p = p;
  tree->c = c;
  tree->s = p;
  tree->w = p;
  tree->left = NULL;
  tree->right = NULL;
  return tree;
}

void treeAdd(struct ITree* tree, int p, char c) {
  if (tree == NULL) {
    return;
  }
  if (p < tree->p) {
    if (tree->left != NULL) {
      return treeAdd(tree->left, p, c);
    } else {
      tree->left = treeCreate(p, c);
      return;
    }
  } else if (p > tree->p) {
    if (tree->right != NULL) {
      return treeAdd(tree->right, p, c);
    } else {
      tree->right = treeCreate(p, c);
      return;
    }
  }
  return;
}

struct ITree* treeFind(struct ITree* tree, int p) {
  if (tree == NULL) {
    return NULL;
  }
  if (tree->p < p) {
    return treeFind(tree->right, p);
  }  else if (tree->p > p) {
    return treeFind(tree->left, p);
  } else {
    return tree;
  }
}

struct ITree* treeFindRoot(struct ITree* tree, int p) {
  if (tree == NULL) {
    return NULL;
  }
  if (tree->p < p) {
    if (treeFindRoot(tree->right, p)) {
      return tree;
    } else {
      return NULL;
    }
  }  else if (tree->p > p) {
    if (treeFindRoot(tree->left, p)) {
      return tree;
    } else {
      return NULL;
    }
  } else {
    return tree;
  }
}

void treeAddTree(struct ITree* tree, struct ITree* node) {
  if (node->p <= tree->p) {
    if (tree->left) {
      return treeAddTree(tree->left, node);
    } else {
      tree->left = node;
    }
  } else {
    if (tree->right) {
      return treeAddTree(tree->right, node);
    } else {
      tree->right = node;
    }
  }
}

struct ITree* treeJoin(struct ITree* a, struct ITree* b) {
  if (a == NULL) {
    return b;
  }
  if (b == NULL) {
    return a;
  }
  struct ITree* bl = b->left;
  struct ITree* br = b->right;
  b->left = NULL;
  b->right = NULL;
  treeAddTree(a, b);
  treeJoin(a, bl);
  treeJoin(a, br);
  return a;
}

void treeCombine(struct ITree* a, struct ITree* b) {
  if (a == NULL || b == NULL) {
    return;
  }
  if (a->p > b->p) {
    if (a->left) {
      return treeCombine(a->left, b);
    } else {
      a->left = b;
      return;
    }
  } else if (a->p < b->p) {
    if (a->right) {
      return treeCombine(a->right, b);
    } else {
      a->right = b;
      return;
    }
  }
};

// pre-order traversal
void treeTraversalPre(struct ITree* tree, struct ITree** target, int* n) {
  if (tree == NULL) {
    return;
  }
  target[(*n)++] = tree;
  treeTraversalPre(tree->left, target, n);
  treeTraversalPre(tree->right, target, n);
}

// in-order traversal
void treeTraversalIn(struct ITree* tree, struct ITree** target, int* n) {
  if (tree == NULL) {
    return;
  }
  treeTraversalIn(tree->left, target, n);
  target[(*n)++] = tree;
  treeTraversalIn(tree->right, target, n);
}

// post-order traversal
void treeTraversalPost(struct ITree* tree, struct ITree** target, int* n) {
  if (tree == NULL) {
    return;
  }
  treeTraversalPost(tree->left, target, n);
  treeTraversalPost(tree->right, target, n);
  target[(*n)++] = tree;
}

void freeTree(struct ITree* tree) {
  if (tree == NULL) {
    return;
  }
  if (tree->left) {
    freeTree(tree->left);
  }
  if (tree->right) {
    freeTree(tree->right);
  }
  free(tree);
}

void fillRoadWeightAndSourceBySource(struct ITree** maps, int n, int s, int tw, int ts) {
  int i = 0;
  for (i = 0; i < n; ++i) {
    if (maps[i]->s == s) {
      maps[i]->w = tw;
      maps[i]->s = ts;
    }
  }
}

char* smallestStringWithSwapsDijkstra(char* s, int** pairs, int n, int* coln) {
  if (n <= 0) {
    return s;
  }
  int i = 0;
  int j = 0;
  int sn = strlen(s);
  struct ITree** maps = (struct ITree**)malloc(sizeof(struct ITree*) * sn);
  for (i = 0; i < sn; ++i) {
    maps[i] = treeCreate(i, s[i]);
  }
  for (i = 0; i < n; ++i) {
    int l = pairs[i][0];
    int r = pairs[i][1];
    int wl = maps[l]->w;
    int wr = maps[r]->w;
    printf("l: %d, r: %d, wl: %d, wr: %d\n", l, r, wl, wr);
    if (wl < wr) {
      maps[r]->w = wl;
      fillRoadWeightAndSourceBySource(maps, sn, maps[r]->s, wl, maps[l]->s);
      for (j = 0; j < sn; ++j) {
        printf("%d%c", maps[j]->w, j == sn - 1 ? '\n' : ' ');
      }
      maps[r]->s = maps[l]->s;
      fillRoadWeightAndSourceBySource(maps, sn, r, wl, maps[l]->s);
      for (j = 0; j < sn; ++j) {
        printf("%d%c", maps[j]->w, j == sn - 1 ? '\n' : ' ');
      }
    } else if (wl > wr) {
      maps[l]->w = wr;
      fillRoadWeightAndSourceBySource(maps, sn, maps[l]->s, wr, maps[r]->s);
      for (j = 0; j < sn; ++j) {
        printf("%d%c", maps[j]->w, j == sn - 1 ? '\n' : ' ');
      }
      maps[l]->s = maps[r]->s;
      fillRoadWeightAndSourceBySource(maps, sn, l, wr, maps[r]->s);
      for (j = 0; j < sn; ++j) {
        printf("%d%c", maps[j]->w, j == sn - 1 ? '\n' : ' ');
      }
    }
  }
  for (i = 0; i < sn; ++i) {
    printf("%c%c", s[i], i == sn - 1 ? '\n' : ' ');
  }
  for (i = 0; i < sn; ++i) {
    printf("%d%c", maps[i]->w, i == sn - 1 ? '\n' : ' ');
  }

  // TODO, implements
  //

  for (i = 0; i < sn; ++i) {
    free(maps[i]);
  }
  free(maps);
  char* ret = malloc(sizeof(char));
  *ret = '\0';
  return ret;
}

char* smallestStringWithSwapsBST(char* s, int** pairs, int n, int* pairsColSize) {
  if (n <= 0) {
    return s;
  }
  // The string can be seen as a graph and s[i] is endpoint, pairs[i] is edge
  int i = 0;
  int j = 0;
  int sn = strlen(s);
  struct ITree** tree = (struct ITree**)malloc(sizeof(struct ITree*) * sn);
  struct ITree* tp;
  int gn = 0;
  for (i = 0; i < sn; ++i) {
    tree[i] = NULL;
  }
  // pre-proc
  // build multi graph, each graph represented by a binary search tree
  for (i = 0; i < n; ++i) {
    int l = pairs[i][0];
    int r = pairs[i][1];
    int ri;
    struct ITree* lt = NULL;
    struct ITree* rt = NULL;
    // Check if endpoint was added to an existed tree
    for (j = 0; j < gn && !(lt = treeFindRoot(tree[j], l)); ++j);
    for (j = 0, ri = 0; j < gn && !(rt = treeFindRoot(tree[j], r)); ri = ++j);
    // printf("gn: %d, l: %d, r: %d\n", gn, l, r);
    // printf("lt: %p, rt: %p\n", lt, rt);
    if (lt == NULL && rt == NULL) {
      // Add new tree
      tree[gn] = treeCreate(l, s[l]);
      // printf("tree[gn]: %p\n", tree[gn]);
      treeAdd(tree[gn], r, s[r]);
      ++gn;
    } else if (lt == NULL) {
      treeAdd(rt, l, s[l]);
    } else if (rt == NULL) {
      treeAdd(lt, r, s[r]);
    } else if (lt != rt) {
      // The endpoint exist in two tree, merge them
      treeJoin(lt, rt);
      tree[ri] = NULL;
    }
  }
  struct ITree** nodes;
  int nn = 0;
  for (i = 0; i < gn; ++i) {
    if (tree[i]) {
      nodes = (struct ITree**)malloc(sizeof(struct ITree*) * 100000);
      nn = 0;
      // Collect endpoints of tree
      treeTraversalIn(tree[i], nodes, &nn);
      // Sort, just swap the value, do not swap the index
      treeQuickSort(nodes, 0, nn - 1);
      free(nodes);
    }
  }
  // Combine all graph
  for (i = 0, tp = NULL; i < gn; ++i) {
    if (tree[i]) {
      if (tp == NULL) {
        tp = tree[i];
      } else {
        treeJoin(tp, tree[i]);
        tree[i] = NULL;
      }
    }
  }
  // Fill others character
  for (i = 0; i < sn; ++i) {
    // Duplicate characters will be dropped
    treeAdd(tp, i, s[i]);
  }
  nn = 0;
  nodes = (struct ITree**)malloc(sizeof(struct ITree*) * 100000);
  treeTraversalIn(tp, nodes, &nn);
  char* ret = (char*)malloc(sizeof(char) * (nn + 1));
  for (i = 0; i < nn; ++i) {
    ret[i] = nodes[i]->c;
  }
  ret[i] = '\0';
  free(nodes);
  freeTree(tp);
  free(tree);
  return ret;
}

struct ILink {
  int p;
  struct ILink* next;
};

struct ILink* createILink(int p) {
  struct ILink* link = (struct ILink*)malloc(sizeof(struct ILink));
  link->p = p;
  link->next = NULL;
  return link;
}

void freeLink(struct ILink* link) {
  if (link->next) {
    freeLink(link->next);
  }
  free(link);
}

struct IChar {
  char c;
  int p;
};

void swapICharValue(struct IChar** cs, int l, int r) {
  char c = cs[l]->c;
  cs[l]->c = cs[r]->c;
  cs[r]->c = c;
}

void swapICharIndex(struct IChar** cs, int l, int r) {
  struct IChar* c = cs[l];
  cs[l] = cs[r];
  cs[r] = c;
}

int cmpICharValue(struct IChar* a, struct IChar* b) {
  if (a->c < b->c) {
    return -1;
  } else if (a->c > b->c) {
    return 1;
  } else {
    return 0;
  }
}
int cmpICharIndex(struct IChar* a, struct IChar* b) {
  if (a->p < b->p) {
    return -1;
  } else if (a->p > b->p) {
    return 1;
  } else {
    return 0;
  }
}

void qsortIChar(
    struct IChar** cs,
    int l, int r,
    int (*cmp) (struct IChar*, struct IChar*),
    void (*swap) (struct IChar**, int, int)) {
  int m = (r - l) / 2 + l;
  int ll = l;
  int rr = r;
  struct IChar mc;
  mc.c = cs[m]->c;
  mc.p = cs[m]->p;
  for (; ll < rr;) {
    for (; cmp(cs[ll], &mc) < 0; ++ll);
    for (; cmp(cs[rr], &mc) > 0; --rr);
    if (ll <= rr) {
      swap(cs, ll++, rr--);
    }
  }
  if (ll < r) {
    qsortIChar(cs, ll, r, cmp, swap);
  }
  if (l < rr) {
    qsortIChar(cs, l, rr, cmp, swap);
  }
}

char* smallestStringWithSwaps(char* s, int** pairs, int n, int* coln) {
  if (n <= 0) {
    return s;
  }
  int i;
  int sn = strlen(s);
  struct ILink** links = (struct ILink**)malloc(sizeof(struct ILink*) * sn);
  for (i = 0; i < sn; ++i) {
    links[i] = createILink(i);
  }
  // Build adjacency list
  for (i = 0; i < n; ++i) {
    int l = pairs[i][0];
    int r = pairs[i][1];
    struct ILink* lp = createILink(l);
    struct ILink* rp = createILink(r);
    rp->next = links[l]->next;
    links[l]->next = rp;
    lp->next = links[r]->next;
    links[r]->next = lp;
  }

  // BFS, mark graph
  int pn = 0;
  int cc[100000];
  int stack[100000];
  int gn = 0;
  memset(cc, 0, sizeof(cc));
  for (i = 0; i < sn; ++i) {
    if (!cc[i]) {
      int p = pn;
      stack[pn++] = i;
      cc[i] = ++gn;;
      // bfs
      for (; p < pn; ++p) {
        struct ILink* pp = links[stack[p]];
        for (; pp; pp = pp->next) {
          if (!cc[pp->p]) {
            stack[pn++] = pp->p;
            cc[pp->p] = cc[i];
          }
        }
      }
    }
  }

  struct IChar** cs = (struct IChar**)malloc(sizeof(struct IChar*) * sn);
  for (i = 0; i < pn; ++i) {
    cs[i] = (struct IChar*)malloc(sizeof(struct IChar));
    cs[i]->p = stack[i];
    cs[i]->c = s[stack[i]];
  }
  int g = 0;
  int l = -1;
  for (i = 0; i < sn; ++i) {
    if (cc[stack[i]] != g) {
      if (l >= 0) {
        // Sort by index
        qsortIChar(cs, l, i - 1, cmpICharIndex, swapICharIndex);
        // Sort by char, do not swap index
        qsortIChar(cs, l, i - 1, cmpICharValue, swapICharValue);
      }
      l = i;
      g = cc[stack[i]];
    }
  }
  if (l < sn) {
    qsortIChar(cs, l, i - 1, cmpICharIndex, swapICharIndex);
    qsortIChar(cs, l, i - 1, cmpICharValue, swapICharValue);
  }
  // Sort all elements with index
  qsortIChar(cs, 0, sn - 1, cmpICharIndex, swapICharIndex);

  char* ret = (char*)malloc(sizeof(char) * (sn + 1));
  for (i = 0; i < sn; ++i) {
    ret[i] = cs[i]->c;
  }
  ret[i] = '\0';

  for (i = 0; i < sn; ++i) {
    freeLink(links[i]);
    free(cs[i]);
  }
  free(cs);
  free(links);
  return ret;
}

int main(int argc, char** argv) {
  int n, i;
  char* s = (char*)malloc(sizeof(char) * 1000000);
  int** pairs;
  int coln;
  int casen = 0;
  for (; scanf("%s", s) != EOF;) {
    printf("case %d, %s:\n", casen++, s);
    scanf("%d", &n);
    pairs = (int**)malloc(sizeof(int*) * n);
    for (i = 0; i < n; ++i) {
      pairs[i] = (int*)malloc(sizeof(int) * 2);
      scanf("%d %d", pairs[i], pairs[i] + 1);
    }
    // char* ret = smallestStringWithSwapsBST(s, pairs, n, &coln);
    // char* ret = smallestStringWithSwapsDijkstra(s, pairs, n, &coln);
    char* ret = smallestStringWithSwaps(s, pairs, n, &coln);
    printf("smallestStringWithSwaps: %s\n", ret);
    free(ret);
    for (i = 0; i < n; ++i) {
      free(pairs[i]);
    }
    free(pairs);
  }
  free(s);
}
