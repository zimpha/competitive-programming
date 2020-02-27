#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;

std::vector<int> dv[N];
int cnt[N], mu[N];

int gcd(int x, int y) {
  return y ? gcd(y, x % y) : x;
}

int main() {
  int n, m = 0;
  scanf("%d", &n);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    cnt[x]++;
    m = std::max(m, x);
  }
  for (int i = 1; i <= m; ++i) {
    mu[i] += i == 1;
    for (int j = i + i; j <= m; j += i) mu[j] -= mu[i];
    for (int j = i; j <= m; j += i) dv[j].push_back(i);
  }
  int64 ret = 1;
  for (int g = 1; g <= m; ++g) {
    int mm = m / g, total = 0;
    std::vector<int> u(mm + 1), v(mm + 1);
    for (int i = 1; i <= mm; ++i) u[i] = cnt[i * g], total += u[i];
    if (total <= 1) continue;
    ret = std::max<int64>(ret, g);
    std::vector<int> stk;
    for (int i = mm; i >= 1; --i) if (u[i]) {
      int cnt = 0;
      for (auto &d: dv[i]) cnt += mu[d] * v[d];
      while (cnt) {
        int j = stk.back(); stk.pop_back();
        if (gcd(i, j) == 1) {
          ret = std::max(ret, (int64)i * j * g);
          --cnt;
        }
        for (auto &d: dv[j]) v[d]--;
      }
      for (auto &d: dv[i]) v[d]++;
      stk.push_back(i);
    }
  }
  printf("%lld\n", ret);
  return 0;
}
