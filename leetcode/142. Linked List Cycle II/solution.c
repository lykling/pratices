#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>


// Definition for singly-linked list.
struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode* detectCycle(struct ListNode* head) {
  struct ListNode* vhead = malloc(sizeof(struct ListNode));
  vhead->val = -1;
  vhead->next = head;
  struct ListNode* slow = vhead;
  struct ListNode* fast = vhead;
  for (; ((fast == vhead) || (fast != NULL && fast != slow)); ) {
    slow = slow->next;
    fast = fast->next;
    if (fast != NULL) {
      fast = fast->next;
    }
  }
  if (fast == NULL) {
    free(vhead);
    return NULL;
  }
  fast = vhead;
  for (; fast != slow; slow = slow->next, fast = fast->next);
  free(vhead);
  return fast;
}

int main(int argc, char** argv) {
  int i, n, p;
  int* nums;
  struct ListNode* nodes;
  while (scanf("%d", &n) != EOF) {
    nums = (int*)malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i) {
      scanf("%d", nums + i);
    }
    scanf("%d", &p);
    nodes = (struct ListNode*)malloc(sizeof(struct ListNode) * n);
    for (i = 0; i < n; ++i) {
      nodes[i].val = nums[i];
      nodes[i].next = nodes + i + 1;
    }
    if (p >= 0) {
      nodes[n - 1].next = nodes + p;
    } else {
      nodes[n - 1].next = NULL;
    }
    struct ListNode* ret = detectCycle(nodes);
    printf("cycle entry: %d\n", ret == NULL ? -1 : ret->val);
    free(nums);
    free(nodes);
  }
  return EXIT_SUCCESS;
}
