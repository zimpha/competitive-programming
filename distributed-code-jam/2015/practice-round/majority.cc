#include "majority.h"
#include <message.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using ll = long long;

const int master_node = 0;
const int sending_node = -1;

const int N = 10000000 + 10;

int A[N];

std::pair<ll, ll> get_range() {
  ll n = GetN();
  ll m = NumberOfNodes();
  ll id = MyNodeId();
  return {n * id / m, n * (id + 1) / m};
}

int main() {
  int m = NumberOfNodes();
  auto range = get_range();
  int L = range.first, R = range.second;
  for (int i = L; i < R; ++i) {
    A[i - L] = GetVote(i);
  }
  int nn = R - L;
  std::sort(A, A + R - L);
  int majority, cnt = 0;
  for (int i = 0, j = 0; i < nn; i = j) {
    for (j = i; j < nn && A[i] == A[j]; ++j);
    if (j - i > cnt) {
      cnt = j - i;
      majority = A[i];
    }
  }
  std::vector<int> candidate;
  if (MyNodeId() == master_node) {
    candidate.push_back(majority);
    for (int node = 1; node < m; ++node) {
      Receive(node);
      candidate.push_back(GetInt(node));
    }
    std::sort(candidate.begin(), candidate.end());
    for (int node = 1; node < m; ++node) {
      for (int i = 0; i < m; ++i) {
        PutInt(node, candidate[i]);
      }
      Send(node);
    }
  } else {
    PutInt(master_node, majority);
    Send(master_node);
  }
  // Second Phase
  if (MyNodeId() != master_node) {
    Receive(master_node);
    for (int i = 0; i < m; ++i) {
      candidate.push_back(GetInt(master_node));
    }
  }
  std::vector<int> count(m);
  for (int i = 0, j = 0, k = 0; i < nn; i = j) {
    for (j = i; j < nn && A[i] == A[j]; ++j);
    while (k < m && candidate[k] < A[i]) ++k;
    while (k < m && candidate[k] == A[i]) {
      count[k] = j - i;
      ++k;
    }
  }
  if (MyNodeId() == master_node) {
    for (int node = 1; node < m; ++node) {
      Receive(node);
      for (int i = 0; i < m; ++i) {
        count[i] += GetInt(node);
      }
    }
    int n = GetN();
    majority = -1;
    for (int i = 0; i < m; ++i) {
      if (count[i] * 2 > n) majority = candidate[i];
    }
    if (majority == -1) puts("NO WINNER");
    else printf("%d\n", majority);
  } else {
    for (int i = 0; i < m; ++i) {
      PutInt(master_node, count[i]);
    }
    Send(master_node);
  }
  return 0;
}
