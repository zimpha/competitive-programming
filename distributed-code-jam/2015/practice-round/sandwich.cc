#include "sandwich.h"
#include <message.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using ll = long long;

const int master_node = 0;
const int sending_node = -1;
const int N = 5000000 + 10;

ll A[N];

std::pair<ll, ll> get_range() {
  ll n = GetN();
  ll m = NumberOfNodes();
  ll id = MyNodeId();
  return {n * id / m, n * (id + 1) / m};
}

int main() {
  auto range = get_range();
  ll L = range.first, R = range.second;
  for (ll i = L; i < R; ++i) {
    A[i - L] = -GetTaste(i);
  }
  int n = R - L;
  ll sum = 0, psum = 0, ssum = 0, max = 0, tmp = 0;
  for (int i = 0; i < n; ++i) {
    tmp = std::max(A[i], A[i] + tmp);
    max = std::max(max, tmp);
    sum += A[i];
    psum = std::max(psum, sum);
  }
  sum = 0;
  for (int i = n - 1; i >= 0; --i) {
    sum += A[i];
    ssum = std::max(ssum, sum);
  }
  if (MyNodeId() == master_node) {
    int m = NumberOfNodes();
    ll ret = max;
    for (int node = 1; node < m; ++node) {
      Receive(node);
      ll now_sum = GetLL(node);
      ll now_psum = GetLL(node);
      ll now_ssum = GetLL(node);
      ll now_max = GetLL(node);
      ret = std::max(ret, now_max);
      ret = std::max(ret, sum + now_psum);
      ret = std::max(ret, ssum + now_sum);
      ret = std::max(ret, ssum + now_psum);
      psum = std::max(psum, sum + now_psum);
      ssum = std::max(now_ssum, ssum + now_sum);
      sum += now_sum;
    }
    printf("%lld\n", -sum + ret);
  } else {
    PutLL(master_node, sum);
    PutLL(master_node, psum);
    PutLL(master_node, ssum);
    PutLL(master_node, max);
    Send(master_node);
  }
  return 0;
}
