#include <cstdio>
#include <queue>
#include <functional>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;
const int64 inf = 1ll << 62;

struct Value {
  std::priority_queue<int64, std::vector<int64>, std::greater<int64>> low, upp;
  int64 mid, low_tag, upp_tag;
  void clear() {
    mid = inf;
    low_tag = upp_tag = 0;
    while (!low.empty()) low.pop();
    while (!upp.empty()) upp.pop();
  }
  std::vector<int64> get() {
    std::vector<int64> ret;
    while (!low.empty()) {
      ret.push_back(low.top() + low_tag);
      low.pop();
    }
    if (mid != inf) ret.push_back(mid);
    while (!upp.empty()) {
      ret.push_back(upp.top() + upp_tag);
      upp.pop();
    }
    std::sort(ret.begin(), ret.end(), std::greater<int64>());
    return ret;
  }
} val[N];

std::vector<std::pair<int, int>> edges[N];
int size[N], n, m;

void dfs(int u, int p = -1) {
  size[u] = 1;
  int pivot = -1, weight = -1;
  for (auto &e: edges[u]) if (e.first != p) {
    dfs(e.first, u);
    if (pivot == -1 || size[e.first] > size[pivot]) pivot = e.first, weight = e.second;
    size[u] += size[e.first];
  }
  if (pivot == -1) {
    val[u].low.push(0);
    return;
  }
  std::swap(val[u], val[pivot]);
  val[u].low_tag += weight;
  val[u].upp_tag -= weight;
  for (auto &e: edges[u]) {
    int v = e.first;
    if (v == p || v == pivot) continue;
    while (!val[v].low.empty()) {
      int64 w = val[v].low.top() + val[v].low_tag + e.second;
      val[u].low.push(w - val[u].low_tag);
      val[v].low.pop();
    }
    if (val[v].mid != inf) val[u].low.push(val[v].mid - val[u].low_tag);
    while (!val[v].upp.empty()) {
      int64 w = val[v].upp.top() + val[v].upp_tag - e.second;
      val[u].low.push(w - val[u].low_tag);
      val[v].upp.pop();
    }
  }
  val[u].low.push(-val[u].low_tag);
  while (val[u].low.size() > m / 2) {
    int64 w = val[u].low.top() + val[u].low_tag;
    val[u].low.pop();
    if (m & 1) {
      if (val[u].mid == inf || val[u].mid < w) std::swap(w, val[u].mid);
    }
    if (w != inf) val[u].upp.push(w - val[u].upp_tag);
  }
  //printf("u=%d %d %lld %d\n", u, (int)val[u].low.size(), val[u].mid, (int)val[u].upp.size());
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i) {
      edges[i].clear();
      val[i].clear();
    }
    for (int i = 1; i < n; ++i) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      edges[u - 1].emplace_back(v - 1, w);
      edges[v - 1].emplace_back(u - 1, w);
    }
    dfs(0);
    auto dp = val[0].get();
    //for (auto &e: dp) printf("%lld ", e);
    //puts("");
    int64 ret = 0;
    for (int i = 0; i < m; ++i) ret += dp[i];
    printf("%lld\n", ret * 2);
  }
  return 0;
}
