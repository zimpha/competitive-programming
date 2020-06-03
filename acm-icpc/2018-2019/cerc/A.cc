#include <cstdio>
#include <cstring>
#include <vector>
#include <unordered_set>

const int N = 300000 + 10;
const int seed = 1e9 + 7;

using uint64 = unsigned long long;

std::unordered_set<uint64> words[N];
uint64 hash[N], pw[N];
char s[N], t[N];
int dp[N][20], lg[N];

int main() {
  int L, n;
  scanf("%d%s", &L, s + 1);
  n = strlen(s + 1);
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * seed;
  hash[n + 1] = 0;
  for (int i = n; i >= 0; --i) hash[i] = hash[i + 1] * seed + s[i];
  for (int i = 0; i < L; ++i) {
    scanf("%s", t);
    uint64 h = 0;
    int m = strlen(t);
    for (int j = m - 1; j >= 0; --j) h = h * seed + t[j];
    words[m].insert(h);
  }
  std::vector<int> len;
  for (int i = 1; i < N; ++i) {
    if (!words[i].empty()) len.push_back(i);
  }
  lg[0] = -1;
  for (int i = 1; i <= n + 1; ++i) lg[i] = lg[i >> 1] + 1;
  dp[0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    dp[i][0] = 1e9;
    for (auto &l: len) if (i >= l) {
      auto h = hash[i - l + 1] - hash[i + 1] * pw[l];
      if (!words[l].count(h)) continue;
      int a = i - l, b = i - 1, k = lg[b - a + 1];
      auto cost = std::min(dp[b][k], dp[a + (1 << k) - 1][k]);
      dp[i][0] = std::min(dp[i][0], cost + 1);
    }
    for (int j = 1; i + 1 - (1 << j) >= 0; ++j) {
      dp[i][j] = std::min(dp[i][j - 1], dp[i - (1 << (j - 1))][j - 1]);
    }
  }
  if (dp[n][0] == 1e9) dp[n][0] = -1;
  printf("%d\n", dp[n][0]);
  return 0;
}
