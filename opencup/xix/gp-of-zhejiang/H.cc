#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>

using int64 = long long;

const int N = 5e5 + 10;
const int mod = 1e9 + 7;

std::vector<int> edges[N], pred[N];
std::map<int, int> from[N];
int dsu[N], head[N], tail[N], next[N];
int deg[N], prev[N];
;
int64 pw[N];
int n, m;

int get(int x) {
  if (dsu[x] != x) dsu[x] = get(dsu[x]);
  return dsu[x];
}

bool check(const std::vector<int> &path) {
  std::vector<int> idx(n);
  for (int i = 0; i < n; ++i) idx.at(path[i]) = i;
  for (int u = 0; u < n; ++u) {
    for (auto &v : edges[u]) {
      int i = idx[u], j = idx[v];
      if (i < j && i + 1 != j) return false;
    }
  }
  return true;
};

int process(const std::vector<int> &forbid, std::vector<std::pair<int, int>> &extra) {
  for (int i = 0; i < n; ++i) {
    head[i] = tail[i] = dsu[i] = i;
    prev[i] = next[i] = -1;
    deg[i] = 0;
    from[i].clear();
  }
  int cnt = 0;
  for (int i = 0; i < n; ++i) if (!forbid[i]) {
    ++cnt;
    for (auto &v : edges[i]) if (!forbid[v]) {
      deg[i]++; from[v][i]++;
    }
  }
  std::vector<int> queue;
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 1 && !forbid[i]) queue.push_back(i);
  }
  for (size_t i = 0; i < queue.size(); ++i) {
    int ru = get(queue[i]);
    int u = tail[get(queue[i])];
    if (deg[u] != 1) continue;
    int go = -1;
    for (auto &v : edges[u]) if (!forbid[v]) {
      if (get(v) != ru) go = v;
    }
    assert(go != -1);
    int rg = get(go), v = tail[rg];
    if (head[rg] == go) {
      next[u] = go; prev[go] = u;
      dsu[rg] = ru; tail[ru] = v;
      if (from[ru].size() < from[rg].size()) {
        std::swap(from[ru], from[rg]);
      }
      cnt -= 1;
      for (auto &e : from[rg]) from[ru][e.first] += e.second;
      auto it = from[ru].find(v);
      if (it != from[ru].end()) {
        deg[v] -= it->second;
        from[ru].erase(it);
        if (deg[v] == 1) queue.push_back(v);
      }
    } else {
      extra.emplace_back(u, go);
    }
  }
  return cnt;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d", &n, &m);
    pw[0] = 1;
    for (int i = 1; i <= n; ++i) {
      pw[i] = pw[i - 1] * 10 % mod;
    }
    for (int i = 0; i < n; ++i) {
      pred[i].clear();
      edges[i].clear();
    }
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d%d", &u, &v);
      edges[u - 1].push_back(v - 1);
      if (cas == 11660)
        fprintf(stderr, "%d %d\n", u, v);
    }
    for (int i = 0; i < n; ++i) {
      std::sort(edges[i].begin(), edges[i].end());
      edges[i].erase(std::unique(edges[i].begin(), edges[i].end()), edges[i].end());
    }
    std::vector<int> forbid(n);
    for (int i = 0; i < n; ++i) pred[i].clear();
    for (int i = 0; i < n; ++i) {
      for (auto &v : edges[i]) pred[v].push_back(i);
    }

    std::vector<std::pair<int, int>> extra;
    int cnt = process(forbid, extra);

    auto get_sum = [&](const std::vector<int> &path) {
      int64 sum = 0;
      for (int i = 0; i < n; ++i) {
        sum = (sum + (path[i] + 1) * pw[n - 1 - i]) % mod;
      }
      return sum;
    };

    std::vector<std::pair<int, int64>> ret;

    auto brute = [&](int s) {
      std::vector<int> path = {s};
      std::vector<bool> mark(n);
      mark[s] = true;
      for (int i = 1; i < n; ++i) {
        int go = -1, cnt = 0;
        for (auto &x : pred[s]) if (!mark[x]) {
          go = x;
          cnt++;
        }
        if (cnt != 1) break;
        path.push_back(s = go);
        mark[s] = true;
      }
      if (path.size() != n) return;
      std::reverse(path.begin(), path.end());
      if (check(path)) ret.emplace_back(path[0], get_sum(path));
    };

    if (cnt == 1) {
      int u = head[get(0)], v = tail[get(0)];
      std::vector<int> path, idx(n);
      for (int x = u; x != -1; x = next[x]) {
        idx[x] = path.size();
        path.push_back(x);
      }
      int64 sum = get_sum(path);
      std::vector<int> mark(n + 1);
      std::vector<bool> visited(n);
      for (int i = 0; i + 1 < n; ++i) {
        for (auto &v : edges[path[i]]) if (v != path[i + 1]) {
          mark[idx[v] + 1]++;
          mark[i + 1]--;
        }
      }
      for (int i = 1; i <= n; ++i) mark[i] += mark[i - 1];
      int best = -1;
      for (auto &x : edges[v]) {
        visited[idx[x]] = true;
        if (idx[x] != 0 && (best == -1 || best > idx[x]))
          best = idx[x];
      }
      if (best != -1) {
        for (int i = best + 1; i < n; ++i) mark[i]++;
      }
      if (visited[0]) {
        for (int i = 0; i < n; ++i) {
          if (!mark[i]) ret.emplace_back(path[i], sum);
          sum = sum - (path[i] + 1) * pw[n - 1] % mod;
          sum = (sum + mod) % mod;
          sum = (sum * 10 + path[i] + 1) % mod;
        }
      } else {
        ret = {{path[0], sum}};
        int middle = -1;
        for (int i = 0; i < n; ++i) {
          bool found = false;
          for (auto &x : edges[path[i]]) {
            if (idx[x] == 0) found = true;
          }
          if (found) middle = i;
        }
        if (middle != -1) {
          int end = -1;
          for (int i = 1; i <= middle; ++i) {
            for (auto &x: pred[path[i]]) if (idx[x] > middle) {
              end = i;
            }
          }
          if (end != -1) brute(path[end - 1]);
        }
      }
    } else {
      std::vector<std::pair<int, int>> bad;
      for (auto &e : extra) {
        int u = get(e.first), v = get(e.second);
        if (u != v && tail[u] == e.first) bad.push_back(e);
      }
      if (bad.size() >= 1) {
        for (size_t i = 0; i < bad.size() && i < 2; ++i) {
          int u = bad[i].first, v = bad[i].second;
          brute(u);
          std::vector<int> path, idx(n, -1), bad(n + 1);
          for (u = head[get(v)]; u != v; u = next[u]) path.push_back(u);
          for (size_t i = 0; i < path.size(); ++i) idx[path[i]] = i;
          for (size_t i = 1; i < path.size(); ++i) {
            for (auto &x: edges[path[i]]) if (idx[x] != -1 && idx[x] < i) {
              if (idx[x] != 0) bad[idx[x]]++, bad[i]--;
            }
          }
          for (int i = 1; i <= n; ++i) bad[i] += bad[i - 1];
          int end = path[0];
          for (size_t i = 1; i < path.size(); ++i) {
            int found = 0;
            for (auto &x: pred[path[i]]) found |= idx[x] == -1;
            if (found) break;
            if (!bad[i]) end = path[i];
          }
          brute(end);
        }
      }
    }
    std::sort(ret.begin(), ret.end());
    ret.erase(std::unique(ret.begin(), ret.end()), ret.end());
    printf("%d\n", (int)ret.size());
    for (size_t i = 0; i < ret.size(); ++i) {
      printf("%lld", ret[i].second);
      putchar(" \n"[i + 1 == ret.size()]);
    }
  }
  return 0;
}
