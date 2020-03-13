#include <cstdio>
#include <queue>

using int64 = long long;

int main() {
  int n;
  int64 a, b;
  scanf("%d%lld%lld", &n, &a, &b);
  std::priority_queue<int64> pq;
  int64 sum = 1;
  for (int i = 0; i < n; ++i) {
    int64 h;
    scanf("%lld", &h);
    int64 cb = (h - 1) / b + 1;
    int64 ca = (h - 1) % b / a + 2;
    sum += cb;
    if (sum >= ca) {
      sum -= ca;
      pq.push(ca);
    } else if (!pq.empty() && pq.top() > ca) {
      sum += pq.top(); pq.pop();
      sum -= ca; pq.push(ca);
    }
  }
  printf("%d\n", (int)pq.size());
  return 0;
}
