#include <bits/stdc++.h>

long gcd(long a, long b) {
  return b ? gcd(b, a % b) : a;
}

const int N = 10000000;
const int low = -43584804, upp = 4842756;

int cache[9][N];

void prepare() {
  for (int d = 0; d < 9; ++d) {
    int *now = cache[d];
    now[0] = 0;
    for (int i = 1; i < N; ++i) {
      now[i] = now[i / 10] * -(d + 1) + i % 10;
    }
  }
}

int get_value(int n, int d) {
  if (n < N) return cache[d - 1][n];
  else return cache[d - 1][n / 10] * -d + n % 10;
}

long run(int n) {
  std::vector<long> p[11];
  for (long i = 1; i <= 10; ++i) {
    p[i].assign(n + 1, 1);
    for (int j = 1; j <= n; ++j) p[i][j] = (i == 10 ? 10 : -i) * p[i][j - 1];
  }
  int l = n / 2, r = n - l;
  std::set<std::vector<int>> candidate;
  for (int d = 1; d < 10; ++d) {
    std::vector<int> divisors;
    for (int i = 1; i <= d; ++i) {
      if (d % i == 0) divisors.push_back(i);
    }
    int m = divisors.size();
    for (int msk = 1; msk < (1 << m); ++msk) {
      std::vector<int> subset;
      for (int i = 0; i < m; ++i) {
        if (msk >> i & 1) subset.push_back(divisors[i]);
      }
      candidate.insert(subset);
    }
  }
  long ret = p[10][n] / 10;
  for (auto &&roots: candidate) {
    int m = roots.size();
    std::map<std::vector<int>, int> count;
    std::vector<int> hash(m, 0);
    for (int num = 0; num < p[10][l]; ++num) {
      bool flag = true;
      for (int j = 0; j < m; ++j) {
        long now = get_value(num, roots[j]) * p[roots[j]][r];
        if (now < -upp || now > -low) {
          flag = false;
          break;
        }
        hash[j] = now;
      }
      if (flag) count[hash]++;
    }
    int sgn = (m & 1) ? 1 : -1;
    for (int num = 1; num < p[10][r]; ++num) {
      if (num % 10 == 0) continue;
      bool flag = true;
      for (int j = 0; j < m; ++j) {
        if (num % 10 % roots[j] != 0) flag = false;
        hash[j] = -get_value(num, roots[j]);
      }
      if (!flag) continue;
      auto it = count.find(hash);
      if (it != count.end()) ret += it->second * sgn;
    }
  }
  return ret;
}

int main() {
  prepare();
  std::cout << run(5) << std::endl;
  std::cout << run(6) << std::endl;
  std::cout << run(16) << std::endl;
  return 0;
}
