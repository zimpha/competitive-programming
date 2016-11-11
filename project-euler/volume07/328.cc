#include <bits/stdc++.h>

long right(int s, int n) {
  if (n == 1) return 0;
  if (n == 2) return s + 1;
  if (n == 3) return s + 2;
  int p = 1;
  while (p * 2 <= n) p *= 2;
  int t = n - p + 1;
  int m = p - std::max(0, p / 2 - t);
  if (t <= p / 2) return right(s, m - 1) + s + m;
  else return right(s + m, n - m) + s + m;
}

long right_bis(int s, int n) {
  if (n <= 3) return right(s, n);
  int p = 1;
  while (p * 2 <= n) p *= 2;
  int t = n - p + 1;
  int m = p - std::max(0, p / 2 - t);
  return s + m + right_bis(s + m, n - m);
}

long run(int n) {
  std::vector<long> C(n + 1, 0);
  long ret = 0;
  for (int i = 2, m = 0; i <= n; ++i) {
    ++m;
    C[i] = m + std::max(std::max(C[m - 1], right(m, i - m)), right_bis(m, i - m));
    int upp = m;
    for (int j = 1; j <= 1024 && j <= upp; j <<= 1) {
      int k = upp - j;
      long tmp = k + std::max(std::max(C[k - 1], right(k, i - k)), right_bis(k, i - k));
      if (tmp < C[i]) C[i] = tmp, m = k;
    }
    ret += C[i];
  }
  return ret;
}

int main() {
  std::cout << run(100) << std::endl;
  std::cout << run(200000) << std::endl;
  return 0;
}
