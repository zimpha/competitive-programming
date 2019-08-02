#include <cstdio>
#include <cassert>
#include <vector>
#include <bitset>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> w(n);
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &w[i]);
    sum += w[i];
  }
  std::sort(w.begin(), w.end());
  sum /= 2;
  std::vector<int> dp(sum + 1, -1);
  std::bitset<25001> f;
  f[0] = 1;
  dp[0] = 0;
  int best_w = -1, best_i = -1;
  for (int i = 0; i < n; ++i) {
    auto g = (f << w[i]) & (~f);
    auto h = (f << w[i]) & f;
    for (int x = g._Find_first(); x <= sum; x = g._Find_next(x)) {
      dp[x] = w[i];
      f[x] = 1;
    }
    int x = h._Find_first();
    if (x <= sum) {
      best_i = i;
      best_w = x;
    }
  }
  if (best_w == -1) {
    puts("0 0");
  } else {
    std::vector<int> a, b;
    for (int x = best_w; x != 0; x -= dp[x]) {
      a.push_back(dp[x]);
    }
    b.push_back(w[best_i]);
    for (int x = best_w - b[0]; x != 0; x -= dp[x]) {
      b.push_back(dp[x]);
    }
    printf("%d %d\n", (int)a.size(), (int)b.size());
    for (auto &x: a) printf("%d ", x);
    puts("");
    for (auto &x: b) printf("%d ", x);
    puts("");
  }
  return 0;
}
