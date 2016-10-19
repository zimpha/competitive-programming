#include <bits/stdc++.h>

using LL = long long;

const int p[] = {2, 3, 5, 7, 11, 13};
const int cnt[] = {10, 5, 2, 1, 1, 1};

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

struct num_t {
  LL p, val, phi;
  bool operator < (const num_t &rhs) const {
    return p > rhs.p;
  }
};

std::vector<num_t> ok;

void dfs(int d, LL now) {
  if (d == 6) {
    if (is_prime(now + 1)) {
      ok.push_back((num_t){now + 1, now + 1, now});
    }
    return;
  }
  for (int i = 0; i <= cnt[d]; ++i) {
    dfs(d + 1, now);
    now *= p[d];
  }
}

const LL mul = 6227020800ll, upper = 1ll << 60;
std::vector<LL> ans;

void solve(int d, LL now, LL phi) {
  if (mul % phi) return;
  if (mul == phi) {
    ans.push_back(now);
  }
  for (size_t i = d; i < ok.size(); ++i) if (now % ok[i].p) {
    if (mul / phi % ok[i].phi == 0 && now <= upper / ok[i].val) {
      solve(i + 1, now * ok[i].val, phi * ok[i].phi);
    }
    if (ans.size() == 2000000) return;
  }
}

LL run(int n) {
  ok.clear();
  dfs(0, 1);
  for (int i = 0; i < 6; ++i) {
    int pw = p[i];
    for (int e = 2; e <= cnt[i] + 1; ++e) {
      pw *= p[i];
      ok.push_back((num_t){p[i], pw, pw / p[i] * (p[i] - 1)});
    }
  }
  std::sort(ok.begin(), ok.end());
  ans.clear();
  solve(0, 1, 1);
  std::sort(ans.begin(), ans.end());
  return ans[n - 1];
}

int main() {
  std::cout << run(150000) << std::endl;
  return 0;
}
