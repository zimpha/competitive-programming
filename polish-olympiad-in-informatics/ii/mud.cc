#include <cstdio>
#include <vector>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> cost(n), sum(n);
  std::vector<std::vector<std::pair<int, int>>> rail(n);
  for (int i = 0; i < n; ++i) {
    int t, s = 0;
    scanf("%d", &t);
    for (int j = 0; j < t; ++j) {
      int x, y;
      scanf("%d%d", &x, &y);
      s += x;
      rail[i].emplace_back(x, y);
      cost[i] += y * s;
      sum[i] += y;
    }
  }
  int best = 0;
  int sx = 0, sy = 0;
  for (int i = 0; i < n; ++i) best += cost[i];
  for (int i = 0; i < n; ++i) {
    int now = 0, cnt = m;
    for (int j = 0; j < n; ++j) if (i != j) {
      now += cost[j];
      cnt += sum[j];
    }
    for (size_t j = 0; j < rail[i].size(); ++j) {
      now += cnt * rail[i][j].first;
      cnt += rail[i][j].second;
      int dis = 0, sum = now;
      for (size_t k = j + 1; k < rail[i].size(); ++k) {
        dis += rail[i][k].first;
        sum += rail[i][k].second * dis;
      }
      if (sum < best) {
        best = sum;
        sx = i + 1;
        sy = j + 1;
      }
    }
  }
  printf("%d\n%d %d\n", best, sx, sy);
  return 0;
}
