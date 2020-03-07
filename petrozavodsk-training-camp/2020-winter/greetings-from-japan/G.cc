#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1000 + 10;

char s[20];
int mask[N];
int len[N];
int dp[N][20];
int n;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    len[i] = strlen(s);
    for (int j = 0; j < len[i]; ++j) {
      mask[i] = mask[i] * 2 + s[j] - '0';
    }
    for (int j = 0; j <= len[i]; ++j) {
      dp[i][j] = -1;
    }
  }
  std::priority_queue<std::pair<int, int>> pq;
  for (int i = 0; i < n; ++i) {
    dp[i][len[i]] = len[i];
    pq.emplace(-len[i], i * 20 + len[i]);
  }
  while (!pq.empty()) {
    int w = -pq.top().first;
    int u = pq.top().second / 20;
    int e = pq.top().second % 20;
    pq.pop();
    if (e == 0) {
      printf("%d\n", w);
      return 0;
    }
    if (dp[u][e] < w) continue;
    auto mue = mask[u] & ((1 << e) - 1);
    for (int v = 0; v < n; ++v) {
      if (u == v && e == len[u]) continue;
      int nu = -1, ne = -1, cost = -1;
      if (len[v] <= e) {
        if ((mue >> (e - len[v])) == mask[v]) {
          nu = u, ne = e - len[v], cost = 0;
        }
      } else {
        if (mue == (mask[v] >> (len[v] - e))) {
          nu = v, ne = len[v] - e, cost = ne;
        }
      }
      if (nu == -1) continue;
      if (dp[nu][ne] == -1 || dp[nu][ne] > w + cost) {
        dp[nu][ne] = w + cost;
        pq.emplace(-w - cost, nu * 20 + ne);
      }
    }
  }
  puts("0");
  return 0;
}
