#include <bits/stdc++.h>
using namespace std;

void sol() {
  int n, m; scanf("%d%d", &n, &m);
  vector<int> xs, ys;
  int q; scanf("%d", &q);
  for (int i = 0; i < q; ++ i) {
    int x, y; scanf("%d%d", &x, &y);
    xs.push_back(x);
    ys.push_back(y);
  }
  xs.push_back(1);
  xs.push_back(n);
  ys.push_back(1);
  ys.push_back(m);
  sort(xs.begin(), xs.end());
  sort(ys.begin(), ys.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  int xMin(n), xMax(0), yMin(m), yMax(0);
  for (size_t i = 1; i < xs.size(); ++ i) {
    xMin = min(xMin, xs[i] - xs[i - 1]);
    xMax = max(xMax, xs[i] - xs[i - 1]);
  }
  for (size_t i = 1; i < ys.size(); ++ i) {
    yMin = min(yMin, ys[i] - ys[i - 1]);
    yMax = max(yMax, ys[i] - ys[i - 1]);
  }
  printf("%lld %lld %lld\n", 1ll * (xs.size() - 1) * (ys.size() - 1), 1ll * xMin * yMin, 1ll * xMax * yMax);
}

int main() {
  int T; scanf("%d", &T);
  for (int _ = 0; _ < T; ++ _) sol();
  return 0;
}
