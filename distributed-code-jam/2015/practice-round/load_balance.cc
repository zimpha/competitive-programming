#include "load_balance.h"
#include <message.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using ll = long long;

const int master_node = 0;
const int sending_node = -1;

const int N = 60, M = 10000;

ll A[N], rem;
std::vector<ll> sxa[M], sxb[M], sya[M], syb[M];

void generate(int l, int r, std::vector<ll> v[]) {
  int m = r - l;
  for (int mask = 0; mask < (1 << m); ++mask) {
    ll s = 0;
    for (int i = 0; i < m; ++i) {
      if (mask >> i & 1) s += A[l + i];
    }
    v[s % rem].push_back(s);
  }
}

void gen_mod(int mod, std::vector<ll> sa[], std::vector<ll> sb[], std::vector<ll> &v) {
  for (int i = 0; i < rem; ++i) {
    int j = (mod - i + rem) % rem;
    for (auto &&a: sa[i]) for (auto &&b: sb[j]) {
      v.push_back(a + b);
    }
  }
}

int main() {
  srand(23333);
  int n = GetN();
  int nodes = NumberOfNodes();
  int me = MyNodeId();
  rem = nodes * 10 - rand() % nodes;
  ll total = 0;
  for (int i = 0; i < n; ++i) {
    A[i] = GetWeight(i);
    total += A[i];
  }
  int X = n / 2, Y = n - X;
  if (total % 2) {
    if (MyNodeId() == master_node) {
      puts("IMPOSSIBLE");
    }
    return 0;
  }
  generate(0, X / 2, sxa);
  generate(X / 2, X, sxb);
  generate(X, X + Y / 2, sya);
  generate(X + Y / 2, n, syb);
  total /= 2;
  int mod = total % rem;
  int L = me * rem / nodes, R = (me + 1) * rem / nodes;
  bool find = false;
  for (int i = L; i < R && !find; ++i) {
    int lm = i, rm = (mod - lm + rem) % rem;
    std::vector<ll> vx, vy;
    gen_mod(lm, sxa, sxb, vx);
    gen_mod(rm, sya, syb, vy);
    for (auto &&e: vy) e = total - e;
    std::sort(vx.begin(), vx.end());
    std::sort(vy.begin(), vy.end());
    int nx = vx.size(), ny = vy.size();
    for (int x = 0, y = 0; x < nx && y < ny && !find; ) {
      if (vx[x] == vy[y]) find = true, ++x, ++y;
      else if (vx[x] < vy[y]) ++x;
      else ++y;
    }
  }

  if (MyNodeId() == master_node) {
    int m = NumberOfNodes();
    for (int node = 1; node < m; ++node) {
      Receive(node);
      find |= GetLL(node);
    }
    if (find) puts("POSSIBLE");
    else puts("IMPOSSIBLE");
  } else {
    PutLL(master_node, find);
    Send(master_node);
  }
  return 0;
}
