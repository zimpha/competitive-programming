#include "almost_sorted.h"
#include <message.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using ll = long long;

const int master_node = 0;
const int sending_node = -1;

const int N = 3000000 + 10;
const int mod = 1 << 20;

ll A[N];

std::pair<ll, ll> get_range() {
  ll n = NumberOfFiles();
  ll m = NumberOfNodes();
  ll id = MyNodeId();
  return {n * id / m, n * (id + 1) / m};
}

int main() {
  auto range = get_range();
  ll L = range.first, R = range.second;
  int n = NumberOfFiles(), m = MaxDistance();
  ll tl = std::max<ll>(0, L - m);
  ll tr = std::min<ll>(n, R + m);
  for (ll i = tl; i < tr; ++i) {
    A[i - tl] = Identifier(i);
  }
  std::sort(A, A + tr - tl);
  ll ret = 0;
  for (ll i = L; i < R; ++i) {
    ret += A[i - tl] % mod * i % mod;
  }
  ret %= mod;
  if (MyNodeId() == master_node) {
    int m = NumberOfNodes();
    for (int node = 1; node < m; ++node) {
      Receive(node);
      ret += GetLL(node);
    }
    printf("%lld\n", ret % mod);
  } else {
    PutLL(master_node, ret);
    Send(master_node);
  }
  return 0;
}
