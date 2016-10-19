#include <bits/stdc++.h>

//https://en.wikipedia.org/wiki/Coin_problem
long run(int n) {
  std::vector<bool> mark(n, 0);
  std::vector<int> primes;
  for (int i = 2; i < n; ++i) if (!mark[i]) {
    primes.push_back(i);
    for (int j = i * i; j < n; j += i) mark[j] = 1;
  }
  long ret = 0;
  for (auto &&p: primes) for (auto &&q: primes) for (auto &&r: primes) {
    if (p >= q || q >= r || p >= r) continue;
    ret += 2ll * p * q * r - p * q - p * r - q * r; 
  }
  return ret;
}

int main() {
  std::cout << run(5000) << std::endl;
  return 0;
}
