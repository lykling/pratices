#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
  int val;
  struct ListNode *next;
};

void visit(struct ListNode* p) {
  while (p) {
    printf("%d%c", p->val, p->next ? ' ' : '\n');
    p = p->next;
  }
}

struct ListNode* reverseKGroup(struct ListNode* head, int k){
  int kk = k;
  struct ListNode* pp = head;
  struct ListNode* p;
  struct ListNode* lp = NULL;
  struct ListNode* x = NULL;
  struct ListNode* y = NULL;
  struct ListNode* z = NULL;
  for (kk = k - 1, p = pp; kk && p; --kk, p = p->next) {}
  head = p ? p : pp;
  while (p) {
    if (lp) {
      lp->next = p;
    }
    for (x = p->next, y = pp, z = pp->next; y != p;) {
      y->next = x;
      x = y;
      y = z;
      z = z->next;
    }
    p->next = x;
    lp = pp;
    pp = lp->next;
    for (kk = k - 1, p = pp; kk && p; --kk, p = p->next) {}
  }
  return head;
}

int main(int argc, char** argv) {
  int i;
  int n = 10;
  int k = 3;
  int* arr = malloc(sizeof(int) * n);
  struct ListNode* v = malloc(sizeof(struct ListNode));
  struct ListNode* p = v;
  for (i = 0; i < n; ++i) {
    arr[i] = rand() % 10;
  }
  for (i = 0; i < n; ++i) {
    p->next = malloc(sizeof(struct ListNode));
    p->next->val = arr[i];
    p->next->next = NULL;
    p = p->next;
  }
  visit(v->next);
  visit(reverseKGroup(v->next, k));
}
