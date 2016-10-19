#include <bits/stdc++.h>

const int N = 300000 + 10;

int primes[N];

int sieve(int n) {
  int m = 0;
  memset(primes, 0, sizeof(*primes) * (n + 1));
  for (int i = 2; i <= n; ++i) {
    if (!primes[i]) primes[m++] = i;
    for (int j = 0; j < m && primes[j] * i <= n; ++j) {
      primes[i * primes[j]] = 1;
      if (i % primes[j] == 0) break;
    }
  }
  return m;
}

long inv(long a, long m) {
  long r = 1;
  for (long n = m - 2; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

long run(int n) {
  int m = sieve(n);
  std::vector<long> A(m, 1), q(m, 1);
  std::set<long> candidate;
  for (int i = 1; i < m; ++i) {
    for (int j = i; j < m; ++j) {
      if (!A[j]) candidate.insert(primes[j]);
      q[j] = q[j] * primes[i - 1] % primes[j];
    }
    long k = (i + 1 - A[i]) * inv(q[i], primes[i]) % primes[i];
    if (k < 0) k += primes[i];
    for (int j = i + 1; j < m; ++j) {
      A[j] = (A[j] + k * q[j]) % primes[j];
    }
  }
  long ret = 0;
  for (auto &&v: candidate) ret += v;
  return ret;
}

int main() {
  std::cout << run(50) << std::endl;
  std::cout << run(300000) << std::endl;
  return 0;
}
