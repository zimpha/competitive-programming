#include <cstdio>
#include <vector>

using int64 = long long;

const int mod = 1000000000;

inline int fact_p(int n, int p) {
  int r = n / p;
  for (int x = p; x <= n / p; ) {
    r += n / (x *= p);
  }
  return r;
}

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (k > n - 2) {
    puts("-1");
    return 0;
  }
  int m = n + k - 2;
  std::vector<int> mark(m + 1), p;
  for (int i = 2; i <= m; ++i) if (!mark[i]) {
    p.push_back(i);
    for (int j = i; j <= m; j += i) mark[j] = 1;
  }
  m = p.size();
  int64 ret = 1;
  for (int i = 0; i < m; ++i) {
    int cnt = fact_p(n - 3, p[i]) + fact_p(n + k - 2, p[i]);
    cnt -= fact_p(k, p[i]) + fact_p(k - 1, p[i]);
    cnt -= fact_p(n - 1, p[i]) + fact_p(n - 2 - k, p[i]);
    ret = ret * pow_mod(p[i], cnt) % mod;
  }
  printf("%lld\n", ret);
  return 0;
}
