#include <cstdio>
#include <cassert>
#include <vector>
#include <map>

const int N = 1000;

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

bool check(int n, const std::vector<int>& label) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (gcd(label[i], label[j]) == 1) return false;
    }
  }
  std::map<int, int> cnt;
  for (auto &x: label) {
    int m = x;
    for (int i = 2; i * i <= m; ++i) if (m % i == 0) {
      while (m % i == 0) m /= i;
      cnt[i]++;
    }
    if (m > 1) cnt[m]++;
  }
  for (auto &e: cnt) {
    if (e.second >= n / 2 + 1) return false;
  }
  return true;
}

int main() {
  std::vector<bool> mark(N);
  std::vector<int> primes;
  for (int i = 2; i < N; ++i) {
    if (!mark[i]) primes.push_back(i);
    for (int j = i; j < N; j += i) mark[j] = 1;
  }
  int n;
  scanf("%d", &n);
  std::vector<int> label(n, 1);
  if (n == 4) label = {42, 110, 195, 1001};
  else if (n == 7) {
    for (int i = 0; i < n; ++i) {
      label[i] *= primes[i];
      label[(i + 1) % n] *= primes[i];
      label[(i + 2) % n] *= primes[i];
    }
    for (int i = 0; i < n; ++i) {
      label[i] *= primes[i + n];
      label[(i + 3) % n] *= primes[i + n];
    }
  } else {
    std::vector<int> group_label = {714, 2090, 4485, 29029, 215441};
    int m = 10;
    for (int i = 0; i < n; ++i) {
      label[i] = group_label[i % 5] * primes[m++];
    }
  }
  //assert(check(n, label));
  for (int i = 0; i < n; ++i) {
    printf("%d\n", label[i]);
  }
  return 0;
}
