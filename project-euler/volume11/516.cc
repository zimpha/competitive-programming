#include <bits/stdc++.h>

using LL = long long;

const LL M = 1ll << 32;

const int p[] = {2, 3, 5};
std::vector<LL> candidate;

inline LL mul_mod(LL a, LL b, LL mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  LL k = (LL)((long double)a * b / mod);
  LL res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

LL pow_mod_LL(LL a, LL n, LL m) {
  LL res = 1;
  for (a %= m; n; n >>= 1) {
    if (n & 1) res = mul_mod(res, a, m);
    a = mul_mod(a, a, m);
  }
  return res;
}

bool is_prime(LL n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (~n & 1) return false;
  const int u[] = {2,3,5,7,325,9375,28178,450775,9780504,1795265022,0};
  LL e = n - 1, a, c = 0; // 原理：http://miller-rabin.appspot.com/
  while (~e & 1) e >>= 1, ++c;
  for (int i = 0; u[i]; ++i) {
    if (n <= u[i]) return true;
    a = pow_mod_LL(u[i], e, n);
    if (a == 1) continue;
    for (int j = 1; a != n - 1; ++j) {
      if (j == c) return false;
      a = mul_mod(a, a, n);
    }
  }
  return true;
}

void dfs(int d, LL now, LL upp) {
  if (d == 3) {
    if (now + 1 > 5 && is_prime(now + 1)) {
      candidate.push_back(now + 1);
    }
    return;
  }
  for (; ;) {
    dfs(d + 1, now, upp);
    now *= p[d];
    if (now > upp) break;
  }
}

LL dfs_ans(int d, LL now, LL upp) {
  if (d == candidate.size()) return now;
  int e = d < 3 ? 64 : 1;
  LL ret = 0;
  for (int i = 0; i <= e; ++i) {
    ret += dfs_ans(d + 1, now, upp);
    ret %= M;
    if ((__int128)now * candidate[d] > upp) break;
    now *= candidate[d];
  }
  return ret;
}

LL run(LL upp) {
  candidate = {2, 3, 5};
  dfs(0, 1, upp);
  std::sort(candidate.begin(), candidate.end());
  std::cout << candidate.size() << std::endl;
  return dfs_ans(0, 1, upp);
}

int main() {
  std::cout << run(100) << std::endl;
  std::cout << run(1000000000000ll) << std::endl;
  return 0;
}

