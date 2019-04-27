#include <cstdio>
#include <cstring>
#include <array>
#include <queue>

using state = std::array<int, 4>;

int dp[50][50][50][50];

int main() {
  memset(dp, -1, sizeof(dp));
  state s, t;
  for (int i = 0; i < 4; ++i) {
    s[i] = t[i] = 0;
  }
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &s[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &t[i]);
  dp[s[0]][s[1]][s[2]][s[3]] = 0;
  std::queue<state> queue;
  queue.push(s);
  auto bound = s;
  while (!queue.empty()) {
    auto &s = queue.front();
    if (s == t) {
      printf("%d\n", dp[t[0]][t[1]][t[2]][t[3]]);
      return 0;
    }
    int step = dp[s[0]][s[1]][s[2]][s[3]];
    for (int i = 0; i < n; ++i) {
      auto t = s;
      t[i] = 0;
      if (dp[t[0]][t[1]][t[2]][t[3]] == -1) {
        dp[t[0]][t[1]][t[2]][t[3]] = step + 1;
        queue.push(std::move(t));
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) if (i != j) { // s[i] -> s[j]
        int w = std::min(bound[j] - s[j], s[i]);
        if (!w) continue;
        auto t = s;
        t[i] -= w;
        t[j] += w;
        if (dp[t[0]][t[1]][t[2]][t[3]] == -1) {
          dp[t[0]][t[1]][t[2]][t[3]] = step + 1;
          queue.push(std::move(t));
        }
      }
    }
    queue.pop();
  }
  puts("NIE");
  return 0;
}
