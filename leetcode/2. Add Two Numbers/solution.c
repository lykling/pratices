#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode {
  int val;
  struct ListNode *next;
};
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  int sum, carry = 0;
  struct ListNode *p, *pp;
  p = (struct ListNode*)malloc(sizeof(struct ListNode));
  pp = p;
  while (l1 || l2 || carry) {
    sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
    pp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    pp->next->val = sum % 10;
    pp->next->next = NULL;
    pp = pp->next;
    carry = sum / 10;
    l1 && (l1 = l1->next);
    l2 && (l2 = l2->next);
  }
  return p->next;
}

int main(int argc, char **argv) {
  struct ListNode *l1 = NULL;
  struct ListNode *l2 = NULL;
  struct ListNode *p = NULL;
  /* int a[] = {3, 4, 2}; */
  /* int b[] = {4, 6, 5}; */
  int a[] = {2,2,8,4,7,2,0,3,4,1};
  int b[] = {8,7,9,2,7,6,7};
  int i;
  for (i = 0; i < 10; ++i) {
    p = (struct ListNode*)malloc(sizeof(struct ListNode));
    p->val = a[i];
    if (l1 != NULL) {
      p->next = l1;
    }
    l1 = p;
  }
  for (i = 0; i < 7; ++i) {
    p = (struct ListNode*)malloc(sizeof(struct ListNode));
    p->val = b[i];
    if (l2 != NULL) {
      p->next = l2;
    }
    l2 = p;
  }
  p = addTwoNumbers(l1, l2);
  while (p != NULL) {
    printf("%d\n", p->val);
    p = p->next;
  }
  return EXIT_SUCCESS;
}