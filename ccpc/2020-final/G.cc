#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 2e5 + 10;
const int mod = 1e9 + 7;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

struct Value {
  std::vector<int64> v;
  int64 mul, add;
  void merge(const Value& r) {
    int d = r.v.size(), n = v.size();
    auto apply = (r.v[0] * r.mul + r.add) % mod;
    mul = mul * apply % mod;
    add = add * apply % mod;
    int64 iapply = pow_mod(apply, mod - 2);
    int64 imul = pow_mod(mul, mod - 2);
    for (int i = 0; i < d; ++i) {
      auto rv = (r.v[d - 1 - i] * r.mul + r.add) % mod;
      auto mv = (v[n - 1 - i] * mul + add) % mod;
      v[n - 1 - i] = (mv * rv % mod * iapply % mod - add + mod) * imul % mod;
    }
  }
  void append() {
    add += 1;
    v.push_back((1 - add + mod) * pow_mod(mul, mod - 2) % mod);
  }
  void build() {
    for (auto &x: v) x = (x * mul + add) % mod;
    std::reverse(v.begin(), v.end());
    for (int i = v.size() - 1; i > 0; --i) {
      v[i] = (v[i] - v[i - 1] + mod) % mod;
    }
  }
  void clear() {
    mul = 1;
    add = 0;
    v = {1};
  }
} val[N];

std::vector<int> edges[N];
Value* dp[N];
int64 g[N][4];
int depth[N];

void dfs(int u, int p = -1) {
  std::vector<Value*> vs;
  depth[u] = 1;
  for (auto &v: edges[u]) if (v != p) {
    dfs(v, u);
    vs.emplace_back(dp[v]);
    depth[u] = std::max(depth[u], depth[v] + 1);
  }
  std::sort(vs.begin(), vs.end(), [&](Value *a, Value *b) {
    return a->v.size() < b->v.size();
  });
  if (vs.empty()) dp[u] = val + u;
  else {
    for (size_t i = 1; i < vs.size(); ++i) {
      vs[i]->merge(*vs[i - 1]);
    }
    dp[u] = vs.back();
  }
  dp[u]->append();
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) edges[i].clear();
    for (int i = 0; i < n; ++i) val[i].clear();
    for (int i = 1; i < n; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      --x, --y;
      edges[x].push_back(y);
      edges[y].push_back(x);
    }
    std::vector<Value*> vs;
    for (auto &u: edges[0]) {
      dfs(u, 0);
      depth[0] = std::max(depth[0], depth[u]);
      dp[u]->build();
      vs.push_back(dp[u]);
    }
    std::sort(vs.begin(), vs.end(), [](Value *a, Value *b) {
      return a->v.size() > b->v.size();
    });
    int64 suffix = 1, ret = 1;
    int last = vs.size() - 1;
    for (int d = 1; d <= depth[0]; ++d) {
      while (last >= 0 && vs[last]->v.size() <= d) {
        suffix = vs[last]->v.back() * suffix % mod;
        --last;
      }
      memset(g[0], 0, sizeof(g[0]));
      g[0][0] = 1;
      for (size_t i = 0; i <= vs.size(); ++i) {
        if (i == vs.size() || vs[i]->v.size() <= d) {
          ret += g[i][2] * suffix % mod;
          break;
        }
        memset(g[i + 1], 0, sizeof(g[i + 1]));
        for (int j = 0; j <= 2; ++j) if (g[i][j]) {
          int jj = std::min(j + 1, 2);
          g[i + 1][jj] = (g[i + 1][jj] + g[i][j] * vs[i]->v[d]) % mod;
          if (d) {
            g[i + 1][j] = (g[i + 1][j] + g[i][j] * vs[i]->v[d - 1]) % mod;
          }
        }
        if (d) vs[i]->v[d] = (vs[i]->v[d] + vs[i]->v[d - 1]) % mod;
      }
    }
    printf("Case #%d: %lld\n", cas, ret % mod);
  }
}
