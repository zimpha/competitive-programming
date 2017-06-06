#include "crates.h"
#include <message.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using ll = long long;

const int master_node = 0;
const int sending_node = -1;
const int inf = 1e9;
const int N = 10000000 + 10;
const int mod = 1e9 + 7;

ll A[N];

int main() {
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  int n = GetNumStacks();
  int L = 1ll * n * me / nodes, R = 1ll * n * (me + 1) / nodes;
  ll sum = 0;
  for (int i = L; i < R; ++i) {
    A[i - L] = GetStackHeight(i + 1);
    sum += A[i - L];
  }
  std::vector<ll> psum(nodes);
  ll total = 0, ssum = 0;
  if (me != master_node) {
    PutLL(master_node, sum);
    Send(master_node);
  } else {
    total += sum;
    for (int node = 1; node < nodes; ++node) {
      psum[node] = total;
      Receive(node);
      total += GetLL(node);
    }
  }
  if (me != master_node) {
    Receive(master_node);
    total = GetLL(master_node);
    ssum = GetLL(master_node);
  } else {
    for (int node = 1; node < nodes; ++node) {
      PutLL(node, total);
      PutLL(node, psum[node]);
      Send(node);
    }
  }
  ll rem = total % n, avg = total / n;
  ll ret = 0, need = 0;
  if (L <= rem) need = (avg + 1) * L;
  else need = (avg + 1) * rem + avg * (L - rem);
  //ret += std::abs(need - ssum);
  A[0] += ssum - need;
  //printf("%lld %lld\n", ssum, need);
  for (int i = L; i < R; ++i) {
    ll expect = avg + (i < rem);
    ret += std::abs(expect - A[i - L]) % mod;
    A[i - L + 1] += A[i - L] - expect;
  }
  ret %= mod;
  if (me != master_node) {
    PutLL(master_node, ret);
    Send(master_node);
  } else {
    for (int node = 1; node < nodes; ++node) {
      Receive(node);
      ret += GetLL(node);
    }
    ret %= mod;
    printf("%lld\n", ret);
  }
  return 0;
}
