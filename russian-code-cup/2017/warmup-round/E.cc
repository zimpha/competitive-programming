#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

const int N = 1000000 + 10;
std::vector<int> rec[N], adj[N];
std::vector<std::pair<int, int>> edges;
int deg[N];

int main() {
  int n, m = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a > b) std::swap(a, b);
    rec[a].push_back(b);
    if (a != b) rec[b].push_back(a);
    m = std::max(m, b);
  }
  long long ret = -1;
  for (int a = 1; a <= m; ++a) {
    std::map<int, int> cnt;
    for (auto &&e: rec[a]) cnt[e]++;
    if (cnt[a] >= 6) ret = std::max(ret, 1ll * a * a * a);
    if (cnt[a] >= 2) {
      for (auto &&e: cnt) {
        if (e.second >= 4 && e.first != a) {
          ret = std::max(ret, 1ll * a * a * e.first);
        }
      }
    }
    for (auto &&e: cnt) {
      if (e.second >= 2 && a < e.first) {
        edges.emplace_back(a, e.first);
        ++deg[a];
        ++deg[e.first];
      }
    }
  }
  for (auto &&e: edges) {
    if (deg[e.first] < deg[e.second]) adj[e.first].push_back(e.second);
    else adj[e.second].push_back(e.first);
  }
  std::vector<bool> mark(m + 1, 0);
  for (int a = 1; a <= m; ++a) {
    for (auto &&b: adj[a]) mark[b] = true;
    for (auto &&b: adj[a]) {
      for (auto &&c: adj[b]) if (mark[c]) {
        ret = std::max(ret, 1ll * a * b * c);
      }
    }
    for (auto &&b: adj[a]) mark[b] = false;
  }
  printf("%lld\n", ret);
  return 0;
}
