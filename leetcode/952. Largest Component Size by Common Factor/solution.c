#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <time.h>

struct ILink {
  int num;
  struct ILink* next;
};

struct ILink* createILink(int n) {
  struct ILink* link = (struct ILink*)malloc(sizeof(struct ILink));
  link->num = n;
  link->next = NULL;
  return link;
}

int mark[100001];
struct ILink adjacency[100001];
int adjacency_init_pos = 2;
bool adjacency_init_mark = false;

void initAdjacency(int maxn) {
  // Init adjacency list and cache it
  if (!adjacency_init_mark) {
    adjacency_init_mark = true;
    memset(mark, 0, sizeof(mark));
    memset(adjacency, 0, sizeof(adjacency));
  }
  if (adjacency_init_pos <= maxn) {
    for (int i = adjacency_init_pos; i <= maxn; ++i) {
      adjacency[i].num = i;
      adjacency[i].next = NULL;
    }
    for (int i = 2; i <= maxn; ++i) {
      if (!mark[i]) {
        int pos = adjacency_init_pos - ((adjacency_init_pos - 1) % i + 1) + i;
        if (i + i > pos) {
          pos = i + i;
        }
        for (int j = pos; j <= maxn; j += i) {
          mark[j] = 1;
          struct ILink* li = createILink(i);
          li->next = adjacency[j].next;
          adjacency[j].next = li;
          struct ILink* lj = createILink(j);
          lj->next= adjacency[i].next;
          adjacency[i].next = lj;
        }
      }
    }
    adjacency_init_pos = maxn + 1;
  }
}

int prime[100001];
uint64_t factors[100001][160];
bool factors_init_mark = false;

void initFactors() {
  if (!factors_init_mark) {
    memset(mark, 0, sizeof(mark));
    memset(prime, 0, sizeof(prime));
    memset(factors, 0, sizeof(factors));

    // Sieve, mark the prime
    for (int i = 2, pn = 0; i < 100001; ++i) {
      if (!mark[i]) {
        prime[i] = pn++;
        int block = prime[i] / 64;
        uint64_t offset = prime[i] % 64;
        factors[i][block] = 1 << offset;
        for (int j = i + i; j < 100001; j += i) {
          mark[j] = 1;
          factors[j][block] |= factors[i][block];
        }
      }
    }
  }
}

bool comFactors(int a, int b) {
  for (int i = 0; i < 123; ++i) {
    if (factors[a][i] & factors[b][i]) {
      return true;
    }
  }
  return false;
}

int bcd(int a, int b) {
  int rm = a % b;
  if (rm == 0) {
    return b;
  }
  return bcd(b, rm);
}

void freeILink(struct ILink* link) {
  if (link == NULL) {
    return;
  }
  if (link->next != NULL) {
    freeILink(link->next);
    link->next = NULL;
  }
  free(link);
}

int largestComponentSizeNN(int* A, int n) {
  struct ILink links[100001];
  for (int i = 0; i < 100001; ++i) {
    links[i].num = 0;
    links[i].next = NULL;
  }
  for (int i = 0; i < n; ++i) {
    links[A[i]].num = A[i];
    links[A[i]].next = NULL;
  }

  initFactors();

  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      // bcd(A[i], A[j]) > 1
      // (mark(A[i]) || mark[A[j]]) && (bcd(A[i], A[j]) > 1)
      // comFactors(A[i], A[j])
      if (comFactors(A[i], A[j])) {
        struct ILink* lp = createILink(A[i]);
        struct ILink* rp = createILink(A[j]);
        lp->next = links[A[j]].next;
        links[A[j]].next = lp;
        rp->next = links[A[i]].next;
        links[A[i]].next = rp;
      }
    }
  }

  int gn = 0;
  int l = 0;
  int pn = 0;
  int stack[n];
  int flags[100001];
  int ret = 0;
  memset(flags, 0, sizeof(flags));
  for (int i = 0; i < n; ++i) {
    if (!flags[A[i]]) {
      stack[pn] = A[i];
      flags[A[i]] = ++gn;
      int m = pn - l;
      if (m > ret) {
        ret = m;
      }
      l = pn;
      for (int p = pn++; p < pn; ++p) {
        for (struct ILink* lp = links[stack[p]].next; lp; lp = lp->next) {
          if (!flags[lp->num]) {
            stack[pn++] = lp->num;
            flags[lp->num] = flags[A[i]];
          }
        }
      }
    }
  }
  if (pn - l > ret) {
    ret = pn -l;
  }

  for (int i = 0; i < 100001; ++i) {
    freeILink(links[i].next);
  }

  return ret;
}

int largestComponentSize(int* A, int n) {

  int tag[100001];
  int maxn = 0;
  memset(tag, 0, sizeof(tag));
  for (int i = 0; i < n; ++i) {
    tag[A[i]] = 1;
    if (A[i] > maxn) {
      maxn = A[i];
    }
  }

  // Build adjacency list
  initAdjacency(maxn);
  // struct ILink adjacency[100001];
  // int mark[100001];
  // memset(mark, 0, sizeof(mark));
  // memset(adjacency, 0, sizeof(adjacency));
  // for (int i = 0; i <= maxn; ++i) {
  //   adjacency[i].num = i;
  //   adjacency[i].next = NULL;
  // }
  // for (int i = 2; i <= maxn; ++i) {
  //   if (!mark[i]) {
  //     for (int j = i + i; j <= maxn; j += i) {
  //       mark[j] = 1;
  //       struct ILink* li = createILink(i);
  //       li->next = adjacency[j].next;
  //       adjacency[j].next = li;
  //       struct ILink* lj = createILink(j);
  //       lj->next= adjacency[i].next;
  //       adjacency[i].next = lj;
  //     }
  //   }
  // }


  int flags[100001];
  int stack[100001];
  int pn = 0;
  int ret = 0;
  memset(flags, 0, sizeof(flags));
  memset(stack, 0, sizeof(stack));
  for (int i = 0, gn = 0; i < n; ++i) {
    if (!flags[A[i]]) {
      stack[pn] = A[i];
      int cnt = 1;
      flags[A[i]] = ++gn;
      for (int p = pn++; p < pn; ++p) {
        for (struct ILink* pp = adjacency[stack[p]].next; pp; pp = pp->next) {
          if (pp->num <= maxn && !flags[pp->num]) {
            // Only add target number or prime factor
            if (tag[pp->num] || pp->num < stack[p]) {
              stack[pn++] = pp->num;
              flags[pp->num] = flags[A[i]];
              cnt += tag[pp->num];
            }
          }
        }
      }
      if (cnt > ret) {
        ret = cnt;
      }
    }
  }

  // for (int i = 0; i <= maxn; ++i) {
  //   freeILink(adjacency[i].next);
  //   adjacency[i].next = NULL;
  // }

  return ret;
}

int main(int argc, char** argv) {
  int n, i;
  for (int casecnt = 0; scanf("%d", &n) != EOF;) {
    printf("case %d:\n", casecnt++);
    int nums[n];
    for (i = 0; i < n; ++i) {
      scanf("%d", &nums[i]);
    }
    struct timeval bt, et;
    gettimeofday(&bt, NULL);
    int ret = largestComponentSize(nums, n);
    gettimeofday(&et, NULL);
    double cost = 1000 * (et.tv_sec - bt.tv_sec) + (et.tv_usec - et.tv_usec);
    printf("largestComponentSize: %d, cost: %lf\n", ret, cost);
  }

  for (int i = 0; i < adjacency_init_pos; ++i) {
    freeILink(adjacency[i].next);
    adjacency[i].next = NULL;
  }
  return EXIT_SUCCESS;
}
