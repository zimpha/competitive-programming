#include <bits/stdc++.h>

const int N = 100000000;

int e[N], d[N], p[N];

void sieve() {
  int m = 0;
  for (int i = 2; i < N; ++i) {
    if (!p[i]) p[m++] = i, e[i] = 1, d[i] = 2;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      p[i * p[j]] = 1;
      if (i % p[j] == 0) {
        e[i * p[j]] = e[i] + 1;
        d[i * p[j]] = d[i] / (e[i] + 1) * (e[i] + 2);
        break;
      } else {
        e[i * p[j]] = 1;
        d[i * p[j]] = d[i] * 2;
      }
    }
  }
}

void exgcd(long a, long b, long &g, long &x, long &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}

bool check(long a, long b, long c, long low) {
  long x, y, g;
  exgcd(a, b, g, x, y);
  if (c % g) return false;
  a /= g, b /= g, c /= g;
  x = (x % b * (c % b) % b + b) % b;
  y = (c - a * x) / b;
  if (y >= 0 && x + y >= low) return true;
  long t = -y / a;
  y += a * t;
  x -= b * t;
  while (y < 0) y += a, x -= b;
  if (x < 0 || x + y < low) return false;
  return true;
}

bool is_tatami_free(long r, long s) {
  if (r > s) std::swap(r, s);
  if (r == 1) return s & 1;
  if (r == 2) return 0;
  if (r & 1) return !check(r - 1, r + 1, s, 0);
  if (check(r - 1, r + 1, s, 0)) return 0;
  if (check(r - 1, r + 1, s + 1, 0)) return 0;
  if (check(r - 1, r + 1, s - 1, 1)) return 0;
  return 1;
}

long T(long n) {
  long ret = 0;
  for (int i = 1; i * i <= n; ++i) {
    if (n % i == 0 && is_tatami_free(i, n / i)) ++ret;
  }
  return ret;
}

long run(int n) {
  for (int x = 2; x < N; x += 2) {
    if (d[x] >= n * 2 && T(x) == n) return x;
  }
  return -1;
}

int main() {
  sieve();
  /*
  std::cout << is_tatami_free(7, 10) << std::endl;
  std::cout << is_tatami_free(1, 70) << std::endl;
  std::cout << is_tatami_free(2, 35) << std::endl;
  std::cout << is_tatami_free(5, 14) << std::endl;
  std::cout << is_tatami_free(20, 66) << std::endl;
  std::cout << is_tatami_free(22, 60) << std::endl;
  std::cout << is_tatami_free(24, 55) << std::endl;
  std::cout << is_tatami_free(30, 44) << std::endl;
  std::cout << is_tatami_free(33, 40) << std::endl;
  */
  std::cout << run(1) << std::endl;
  std::cout << run(5) << std::endl;
  std::cout << run(200) << std::endl;
  return 0;
}
