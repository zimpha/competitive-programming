#include "pancakes.h"
#include <message.h>
#include <bits/stdc++.h>

const int N = 1000000 + 10;
int A[N];

int main() {
  int n = GetStackSize();
  int me = MyNodeId();
  int nodes = NumberOfNodes();
  int L = 1ll * n * me / nodes, R = 1ll * n * (me + 1) / nodes;
  for (int i = L; i < R; ++i) {
    A[i - L] = GetStackItem(i);
  }
  int m = R - L;
  int cnt = 1;
  for (int i = 1; i < m; ++i) {
    if (A[i] < A[i - 1]) ++cnt;
  }
  if (m == 0) cnt = 0;
  if (me) {
    PutInt(0, cnt);
    if (cnt) {
      PutInt(0, A[0]);
      PutInt(0, A[m - 1]);
    }
    Send(0);
  } else {
    std::vector<int> size, first, last;
    if (cnt) size.push_back(cnt), first.push_back(A[0]), last.push_back(A[m - 1]);
    for (int node = 1; node < nodes; ++node) {
      Receive(node);
      int cnt = GetInt(node);
      if (cnt) {
        int l = GetInt(node);
        int r = GetInt(node);
        size.push_back(cnt);
        first.push_back(l);
        last.push_back(r);
      }
    }
    int ret = size[0];
    int r = last[0];
    for (size_t i = 1; i < size.size(); ++i) {
      ret += size[i];
      if (first[i] >= r) --ret;
      r = last[i];
    }
    printf("%d\n", ret);
  }
  return 0;
}
