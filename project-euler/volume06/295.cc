#include <bits/stdc++.h>

const long N = 100000 + 10;

long gcd(long a, long b) {
  return b ? gcd(b, a % b) : a;
}

long exgcd(long a, long b, long &x, long &y) {
  if (!b) return x = 1, y = 0, a;
  long g = exgcd(b, a % b, y, x);
  y -= x * (a / b);
  return g;
}

void linear_equation(long a, long b, long c, long &x, long &y) {
  long g = exgcd(a, b, x, y);
  b /= g, a /= g, c /= g;
  x = (x % b * (c % b) % b + b) % b;
  y = (c - a * x) / b;
}

// (x, y) -> ax + by = c
double dis(long x, long y, long a, long b, long c) {
  return abs(1.0 * a * x + 1.0 * b * y - c) / hypot(a, b);
}

std::vector<long> cache[N];
std::map<long, std::vector<long>> mp;
long total;

long dfs(long a, long b, long c, long d, long n) {
  long u = a + c, v = b + d, ret = 0;
  if (u * u > n * 4) return 0;
  if (u % 2 == v % 2) {
    long x, y, w = (u * u - v * v) / 2;
    linear_equation(u, -v, w, x, y);
    while (u * y + v * x >= u * v) x -= v, y -= u;
    while (u * y + v * x <= u * v) x += v, y += u;
    long cx = 0, cy = v - 1;
    double mx = dis(0, v - 1, v, u, u * v);
    for (long i = 0; i < v; ++i) {
      long j = u * (v - i) / v;
      if (!i) --j;
      double d = dis(j, i, v, u, u * v);
      if (d < mx) mx = d, cx = j, cy = i;
    }
    std::vector<long> r;
    for (; ; x += v, y += u) {
      long r2 = x * x + (y - v) * (y - v);
      if (r2 > n * n) break;
      long d2 = (x - cx) * (x - cx) + (y - cy) * (y - cy);
      if (d2 > r2) r.push_back(r2);
    }
    if (r.size()) {
      cache[total++] = r;
      for (auto &&v: r) {
        mp[v].push_back(total - 1);
      }
      ret = (long)r.size() * (r.size() + 1) / 2;
    }
  }
  return ret + dfs(a, b, u, v, n) + dfs(u, v, c, d, n);
}

long run(long n) {
  mp.clear();
  total = 0;
  long ret = dfs(1, 0, 1, 1, n), cnt = 0;
  cache[total].clear();
  for (long i = 1; i <= n; ++i) {
    if (i * i + (i - 1) * (i - 1) > n * n) break;
    cache[total].push_back(i * i + (i - 1) * (i - 1));
    mp[cache[total].back()].push_back(total);
  }
  cnt = cache[total].size();
  ret += cnt * (cnt + 1) / 2;
  std::map<std::vector<long>, long> count;
  for (auto &&x: mp) if (x.second.size() > 1) {
    std::vector<long> &idx = x.second;
    long m = idx.size();
    for (long msk = 1; msk < (1 << m); ++msk) {
      std::vector<long> sub;
      for (long i = 0; i < m; ++i) {
        if (msk >> i & 1) sub.push_back(idx[i]);
      }
      if (sub.size() > 1) count[sub]++;
    }
  }
  for (auto &&x: count) {
    long s = x.first.size();
    long cnt = x.second;
    long delta = cnt * (cnt + 1) / 2;
    if (s & 1) ret += delta;
    else ret -= delta;
  }
  return ret;
}

int main() {
  std::cout << run(10) << std::endl;
  std::cout << run(100) << std::endl;
  std::cout << run(1000) << std::endl;
  std::cout << run(10000) << std::endl;
  std::cout << run(100000) << std::endl;
  return 0;
}
