#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;
const int mod = 1e9 + 7;

struct Entry {
  int root;
  int64 dist;
  int i1, i2;
  Entry(int root, int64 dist, int i1, int i2): root(root), dist(dist), i1(i1), i2(i2) {}
};

std::vector<Entry> entries[N];
std::vector<std::pair<int, int>> edges[N];
std::vector<std::vector<int64>> dis;

namespace centroid {
bool done[N];
int size[N];
int total, mins, root;

void init(int n) {
  for (int i = 0; i < n; ++i) done[i] = 0;
}

void get_center(int u, int p = -1) {
  int mx = 0; size[u] = 1;
  for (auto &e: edges[u]) if (e.first != p && !done[e.first]) {
    get_center(e.first, u);
    size[u] += size[e.first];
    mx = std::max(mx, size[e.first]);
  }
  mx = std::max(mx, total - size[u]);
  if (mx < mins) mins = mx, root = u;
}

int root_index;
void get_dist(int u, int64 dist, int p = -1) {
  entries[u].emplace_back(root, dist, root_index, dis.size() - 1);
  dis[root_index].push_back(dist);
  dis.back().push_back(dist);
  size[u] = 1;
  for (auto &e: edges[u]) if (e.first != p && !done[e.first]) {
    get_dist(e.first, dist + e.second, u);
    size[u] += size[e.first];
  }
}

void work(int u, int tot) {
  total = tot, mins = tot * 2;
  get_center(u);
  done[u = root] = true;
  root_index = dis.size();
  dis.emplace_back();
  dis.back().push_back(0);
  entries[u].emplace_back(root, 0, root_index, -1);
  for (auto &e: edges[u]) if (!done[e.first]) {
    dis.emplace_back();
    get_dist(e.first, e.second, u);
  }
  for (auto &e: edges[u]) if (!done[e.first]) {
    work(e.first, size[e.first]);
  }
}
}

int64 fac[N], ifac[N];
int64 dist[N];
int i2[N];
int cnt[N], n, k, l;

int64 pow_mod(int64 a, int64 n) {
  int64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int count(const std::vector<int64> &d, int64 L, int64 R) {
  if (L > R) return 0;
  return std::upper_bound(d.begin(), d.end(), R) - std::lower_bound(d.begin(), d.end(), L);
}

int64 ways(int n, int k) {
  if (n < k) return 0;
  return fac[n] * ifac[n - k] % mod;
}

int64 solve(int u, int p = -1) {
  int64 ret = 0;
  for (auto &e: edges[u]) if (e.first != p) {
    ret += solve(e.first, u);
  }
  cnt[u] = 0;
  for (auto &e: entries[u]) {
    dist[e.root] = e.dist;
    i2[e.root] = e.i2;
    cnt[u] += count(dis[e.i1], 0, l - e.dist);
    if (e.i2 != -1) cnt[u] -= count(dis[e.i2], 0, l - e.dist);
  }
  ret += ways(cnt[u], k);
  for (auto &e: edges[u]) if (e.first != p) {
    int sub = 0;
    for (auto &x: entries[e.first]) if (dist[x.root] != -1) {
      if (dist[x.root] == 0) {
        sub += count(dis[x.i2], l + 1, l + x.dist);
      } else if (dist[x.root] > x.dist) {
        sub += count(dis[x.i1], l - dist[x.root] + 1, l - x.dist);
        if (i2[x.root] != -1) sub -= count(dis[i2[x.root]], l - dist[x.root] + 1, l - x.dist);
      }
    }
    ret -= ways(cnt[e.first] - sub, k);;
  }
  for (auto &e: entries[u]) dist[e.root] = -1;
  return ret % mod;
}

int main() {
  scanf("%d%d%d", &n, &k, &l);
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edges[u - 1].emplace_back(v - 1, w);
    edges[v - 1].emplace_back(u - 1, w);
  }
  centroid::init(n);
  centroid::work(0, n);
  for (auto& d: dis) std::sort(d.begin(), d.end());
  fac[0] = ifac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * i % mod;
    ifac[i] = pow_mod(fac[i], mod - 2);
  }
  for (int i = 0; i < n; ++i) dist[i] = -1;
  int64 ret = solve(0);
  ret %= mod; ret += mod; ret %= mod;
  printf("%lld\n", ret);
  return 0;
}
