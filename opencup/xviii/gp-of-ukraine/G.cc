#include <cstdio>
#include <vector>
#include <queue>

int main() {
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  std::priority_queue<int> pq;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    x %= a + b;
    if (x >= a || x >= b) {
      pq.push(x);
    }
  }
  int ret = 0;
  while (!pq.empty()) {
    int u = pq.top();
    pq.pop();
    if (ret) u -= b;
    else u -= a;
    if (u < 0) break;
    if (u >= a || u >= b) pq.push(u);
    ret ^= 1;
  }
  if (!ret) puts("Marichka");
  else puts("Zenyk");
  return 0;
}
