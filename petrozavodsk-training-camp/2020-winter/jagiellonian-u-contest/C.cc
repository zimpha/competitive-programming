#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, d;
    scanf("%d%d", &n, &d);
    std::vector<int64> a(n), x(n);
    for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) a[i] -= (int64)i * d;
    std::priority_queue<int64> pq;
    for (int i = 0; i < n; ++i) {
      pq.push(a[i]); pq.push(a[i]);
      x[i] = pq.top(); pq.pop();
    }
    for (int i = n - 2; i >= 0; --i) {
      x[i] = std::min(x[i], x[i + 1]);
    }
    int64 ret = 0;
    for (int i = 0; i < n; ++i) {
      ret += std::abs(a[i] - std::max<int64>(0, x[i]));
    }
    printf("%lld\n", ret);
  }
  return 0;
}
