#include <bits/stdc++.h>

using LL = long long;

LL pm(LL a, LL n, LL m) {
  LL r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

LL S(int p) {
  if (p < 5) return 0;
  // (p-1)! = -1 mod p, (p-2)! = 1 mod p
  // (p-3)! = (p - 1) / 2 mod p
  // (p-4)! = (-1)^(p/3+1) * (p+1)/6 mod p
  // (p-5)! = rh + (r^2-1)/24 mod p, h=p/24, r=p-24h
  LL ret = p + (p - 1) / 2;
  if ((p / 3) & 1) ret += (p + 1) / 6;
  else ret -= (p + 1) / 6;
  int h = p / 24, r = p - 24 * h;
  ret += r * h + (r * r - 1) / 24;
  return ret % p;
}

LL run(int n) {
  std::vector<int> p;
  std::vector<bool> mark(n);
  for (int i = 2; i < n; ++i) {
    if (!mark[i]) p.push_back(i);
    for (size_t j = 0; j < p.size() && p[j] * i < n; ++j) {
      mark[i * p[j]] = true;
      if (i % p[j] == 0) break;
    }
  }
  LL ret = 0;
  for (auto &&x: p) ret += S(x);
  return ret;
}

int main() {
  std::cout << S(7) << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(100000000) << std::endl;
  return 0;
}

