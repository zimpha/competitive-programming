#include <bits/stdc++.h>

inline long sqr(long x) {return x * x;}
inline long cub(long x) {return x * x * x;}

const int SZ = 1000000, MN = 10000;
int pi[SZ], pl[SZ], m;
void sieve() {
  m = 0; for (int i = 2; i < SZ; ++ i) pi[i] = 1;
  for (int i = 2; i < SZ; ++i) {
    if (pi[i]) pl[m++] = i;
    for (int j = 0; j < m && pl[j] * i < SZ; ++j) {
      pi[pl[j] * i] = 0;
      if (i % pl[j] == 0) break;
    }
  }
  for (int i = 2; i < SZ; ++ i) pi[i] += pi[i - 1];
}
std::map<long, long> cache;
long phi(long x, long a) {
  if (a == 1 || !x) return (x + 1) / 2;
  long &r = cache[(x << 10) + a]; if (r) return r;
  return r = phi(x, a - 1) - phi(x / pl[a - 1], a - 1);
}
long get_pi(long n) {
  if (n < SZ) return pi[n];
  long a = get_pi(pow(n, .25));
  long b = get_pi(sqrt(n));
  long c = get_pi(pow(n, 1./3));
  long r = phi(n, a) + (b + a - 2) * (b - a + 1) / 2;
  for (int i = a + 1; i <= b; ++i) {
    long w = n / pl[i - 1];
    r -= get_pi(w);
    if (i <= c) {
      int upp = get_pi(sqrt(w));
      for (int j = i; j <= upp; ++j) r += j - 1 - get_pi(w / pl[j - 1]);
    }
  }
  return r;
}

long S(long n) {
  long ret = get_pi(n);
  if (n >= 4) ret += n / 2 - 1;
  if (n >= 5) ret += get_pi(n - 2) - 1;
  if (n > 5) {
    long a = n - 6 + 1, b = n - n / 2 * 2 + 1;
    ret += (a + b) * ((a - b) / 2 + 1) / 2;
  }
  return ret;
}

long run(int n) {
  std::vector<int> fib = {0, 1};
  for (int i = 2; i <= n; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }
  long ret = 0;
  for (int k = 3; k <= n; ++k) {
    ret += S(fib[k]);
  }
  return ret;
}

int main() {
  sieve();
  std::cout << S(10) << std::endl;
  std::cout << S(100) << std::endl;
  std::cout << S(1000) << std::endl;
  std::cout << run(44) << std::endl;
  return 0;
}
