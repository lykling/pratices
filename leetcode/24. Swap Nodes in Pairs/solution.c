#include <stdio.h>
#include <stdlib.h>


// Definition for singly-linked list.
struct ListNode {
  int val;
  struct ListNode *next;
};



struct ListNode* swapPairs(struct ListNode* head){
  struct ListNode* pp = head;
  struct ListNode* p = pp ? pp->next : NULL;
  struct ListNode* tp = NULL;
  head = p ? p : pp;

  while (p) {
    if (tp) {
      tp->next = p;
    }
    pp->next = p->next;
    p->next = pp;
    tp = pp;
    pp = pp->next;
    p = pp ? pp->next : NULL;
  }
  return head;
}

void visit(struct ListNode* p) {
  while (p) {
    printf("%d%c", p->val, p->next ? ' ' : '\n');
    p = p->next;
  }
}


int main(int argc, char** argv) {
  int i;
  int n = 0;
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
  visit(swapPairs(v->next));
}
