#include <cstdio>
#include <vector>
#include <algorithm>

using i64 = long long;

i64 p[30], cp;
std::vector<i64> vs;

void dfs(int d, i64 w, i64 bound) {
  vs.push_back(w);
  if (d == cp) return;
  for (int i = d; i < cp; ++i) {
    i64 t_bound = bound, t_w = w;
    while (t_bound >= p[i]) {
      t_w *= p[i];
      t_bound /= p[i];
      dfs(i + 1, t_w, t_bound);
    }
  }
}

int main() {
  i64 b, m, n;
  scanf("%lld%lld%lld", &b, &m, &n);
  cp = 0;
  for (int i = 2; i * i <= b; ++i) if (b % i == 0) {
    p[cp++] = i;
    while (b % i == 0) b /= i;
  }
  if (b > 1) p[cp++] = b;
  dfs(0, 1, m);
  std::sort(vs.begin(), vs.end());
  for (int i = 0; i < n; ++i) {
    i64 x;
    scanf("%lld", &x);
    auto it = std::lower_bound(vs.begin(), vs.end(), x);
    if (it == vs.end()) puts("-1");
    else printf("%lld\n", *it - x);
  }
  return 0;
}
