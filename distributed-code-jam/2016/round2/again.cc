#include <message.h>
#include "again.h"
#include <cstdio>
#include <vector>

using ll = long long;

const int master_node = 0;
const int sending_node = -1;
const int mod = 1e9 + 7;

int main() {
  ll SA = 0, SB = 0;
  int n = GetN(), m = NumberOfNodes();
  for (int i = MyNodeId(); i < n; i += m) {
    SA = (SA + GetA(i)) % mod;
    SB = (SB + GetB(i)) % mod;
  }
  std::vector<ll> sa(m), sb(m);
  if (MyNodeId() == master_node) {
    sa[0] = SA, sb[0] = SB;
    for (int node = 1; node < m; ++node) {
      Receive(node);
      sa[node] = GetLL(node);
      Receive(node);
      sb[node] = GetLL(node);
    }
    ll ret = 0;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        if ((i + j) % m) ret = (ret + sa[i] * sb[j]) % mod;
      }
    }
    printf("%lld\n", ret);
  } else {
    PutLL(master_node, SA);
    Send(master_node);
    PutLL(master_node, SB);
    Send(master_node);
  }
  return 0;
}
