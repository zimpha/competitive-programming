#include <cstdio>
#include <cstring>
#include <bitset>
#include <iostream>
#include <algorithm>

const int N = 100000, M = 10000000 + 10;

int S[M];

long pow_mod(long a, long n, long mod) {
  long r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

const int U = 200000000;
std::bitset<U> mark;

void sieve(int n) {
  mark.reset();
  int m = 0;
  for (int i = 2; i < U && m < n; ++i) {
    if (!mark[i]) S[++m] = i;
    for (int j = 1; j <= m && S[j] * i < U; ++j) {
      mark[i * S[j]] = true;
      if (i % S[j] == 0) break;
    }
  }
  for (int i = 1; i <= n; ++i) {
    S[i] = pow_mod(S[i], i, 10007);
  }
}

namespace st {
  const int N = 100000;
  int cnt[N << 2];
  void init() {
    memset(cnt, 0, sizeof(cnt));
  }
  void ins(int rt, int l, int r, int x, int v) {
    cnt[rt] += v;
    if (l + 1 == r) return;
    int m = (l + r) >> 1;
    if (x < m) ins(rt << 1, l, m, x, v);
    else ins(rt << 1 | 1, m, r, x, v);
  }
  int kth(int rt, int l, int r, int k) {
    if (l + 1 == r) return l;
    int m = (l + r) >> 1;
    if (k <= cnt[rt << 1]) return kth(rt << 1, l, m, k);
    else return kth(rt << 1 | 1, m, r, k - cnt[rt << 1]);
  }
}

void F(int n, int m) {
  st::init();
  long ret = 0;
  for (int i = 1; i < m; ++i) {
    st::ins(1, 0, st::N, S[i] + S[i / 10000 + 1], 1);
  }
  for (int i = m; i <= n; ++i) {
    st::ins(1, 0, st::N, S[i] + S[i / 10000 + 1], 1);
    ret += st::kth(1, 0, st::N, m / 2);
    ret += st::kth(1, 0, st::N, m / 2 + 1);
    st::ins(1, 0, st::N, S[i - m + 1] + S[(i - m + 1) / 10000 + 1], -1);
  }
  std::cout << ret / 2 << "." << (5 * (ret % 2)) << std::endl;
}

int main() {
  sieve(10000000);
  F(100, 10);
  F(100000, 10000);
  F(10000000, 100000);
  return 0;
}
