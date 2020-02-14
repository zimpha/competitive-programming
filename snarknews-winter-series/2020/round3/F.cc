#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e5 + 10;

std::vector<int> succ[N], pred[N];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> in(n + 2), out(n + 2);
  int S = n, T = n + 1;
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    succ[u].push_back(v);
    pred[v].push_back(u);
    in[v]++, out[u]++;
  }
  for (int i = 0; i < n; ++i) {
    if (in[i] == 0) succ[S].push_back(i), pred[i].push_back(S), in[i]++;
    if (out[i] == 0) succ[i].push_back(T), pred[T].push_back(i), in[T]++;
  }
  std::vector<int> order, pos(n + 2);
  order = {S};
  for (size_t i = 0; i < order.size(); ++i) {
    int u = order[i];
    for (auto &v: succ[u]) {
      if (--in[v] == 0) order.push_back(v);
    }
  }
  for (int i = 0; i <= n + 1; ++i) pos[order[i]] = i;
  std::vector<int> cnt(n + 2);
  for (int i = 0; i < n; ++i) {
    int best = -1;
    for (auto &v: succ[i]) {
      if (best == -1 || best > pos[v]) best = pos[v];
    }
    if (best != -1) cnt[pos[i] + 1]++, cnt[best]--;
  }
  for (int i = n - 1; i >= 0; --i) {
    int best = -1;
    for (auto &v: pred[i]) {
      if (best == -1 || best < pos[v]) best = pos[v];
    }
    if (best != -1) cnt[best+1]++, cnt[pos[i]]--;
  }
  std::vector<int> ret;
  for (int i = 1; i <= n; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = 1; i <= n; ++i) {
    if (!cnt[i]) ret.push_back(order[i] + 1);
  }
  if (ret.empty()) {
    for (int i = 0; i < n; ++i) ret.push_back(i + 1);
  }
  printf("%d\n", (int)ret.size());
  for (auto &x: ret) printf("%d ", x);
  puts("");
  return 0;
}
