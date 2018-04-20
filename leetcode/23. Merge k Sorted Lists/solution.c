#include <stdio.h>
#include <stdlib.h>


struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  if (listsSize == 0) {
    return NULL;
  }
  if (listsSize == 1) {
    return lists[0];
  }
  struct ListNode *m = (struct ListNode*)malloc(sizeof(struct ListNode));
  struct ListNode *p = m;
  struct ListNode *l = lists[0];
  struct ListNode *r = lists[listsSize - 1];
  while (l && r) {
    if (l->val < r->val) {
      p->next = l;
      l = l->next;
    } else {
      p->next = r;
      r = r->next;
    }
    p = p->next;
  }
  if (l) {
    p->next = l;
  } else {
    p->next = r;
  }
  lists[0] = m->next;
  return mergeKLists(lists, listsSize - 1);
}


void print(struct ListNode* l) {
  while (l) {
    printf("%d%c", l->val, l->next ? ' ' : '\n');
    l = l->next;
  }
}


int main(int argc, char **argv) {
  int i = 0;
  struct ListNode **l = (struct ListNode**)malloc(sizeof(struct ListNode*));
  for (i = 0; i < 3; ++i) {
    // l[i] = (struct ListNode*)malloc(sizeof(struct ListNode));
    l[i] = NULL;
  }
  struct ListNode *p = mergeKLists(l, 3);
  print(p);
  return EXIT_SUCCESS;
}
