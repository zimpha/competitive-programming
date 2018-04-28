#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int MAXN = 200 + 10;
vector<int> G[MAXN];
int cost[MAXN], n;
int D[2], C[2];

struct ans_t {
  int sum;
  bitset<MAXN> u;
  ans_t(): sum(0), u() {}
  ans_t& add(int v) {
    sum += cost[v]; u[v] = 1;
    return *this;
  }
  bool operator < (const ans_t &rhs) const {return sum < rhs.sum;}
  bool operator < (const int &rhs) const {return sum < rhs;}
  ans_t operator + (const ans_t &rhs) const {
    ans_t tmp;
    tmp.sum = sum + rhs.sum;
    tmp.u = u | rhs.u;
    return tmp;
  }
  bool empty() const {return !u.any();}
} f[MAXN][2];

bitset<MAXN> mark;
int bel[MAXN], dep[MAXN];
vector<int> ch[MAXN];
void dfs1(int u, int f, int top) {
  bel[u] = top;
  for (auto &v: G[u]) if (v != f) {
    dfs1(v, u, top);
  }
}
void dfs2(int u, int f, int sep, vector<int> &pt) {
  dep[u] = dep[f] + 1; pt.push_back(u);
  for (auto &v: G[u]) if (v != f && v != sep) {
    dfs2(v, u, sep, pt);
  }
}

void add(ans_t &ret, int lim, vector<int> &pt, int &best) {
  for (auto &x: pt) {
    if (dep[x] < lim) ret.add(x);
    if (dep[x] == lim) {
      if (best == -1 || cost[best] < cost[x]) best = x;
      mark[x] = 1;
    }
  }
}

ans_t solve(int sep, int g, int D, int C) {
  if (D == 0) return ans_t().add(g);
  if (C == 1) return ans_t();
  dep[g] = 0;
  for (auto &v: G[g]) if (v != sep) {
    ch[v].clear();
    dfs2(v, g, sep, ch[v]);
  }
  ans_t ret;
  for (auto &v: G[g]) if (v != sep) {
    if (D == 1) {
      ans_t tmp; tmp.add(g); tmp.add(v);
      if (ret < tmp) ret = tmp;
      continue;
    }
    ans_t tmp; tmp.add(g); mark.reset();
    int best_v = -1, best_u = -1;
    add(tmp, (D + 1) / 2, ch[v], best_v);
    if (best_v == -1) continue;
    for (auto &u: G[g]) if (u != sep && u != v) {
      add(tmp, D / 2, ch[u], best_u);
    }
    if (best_u == -1) continue;
    tmp.add(best_v); tmp.add(best_u);
    mark[best_v] = mark[best_u] = 0;
    vector<int> pc;
    for (int i = 0; i < n; ++i) if (mark[i]) {
      pc.push_back(i);
    }
    sort(pc.begin(), pc.end(), [&](int a, int b) {
      return cost[a] > cost[b];
    });
    for (int i = 0; i < C - 2 && i < pc.size(); ++i) tmp.add(pc[i]);
    if (ret < tmp) ret = tmp;
  }
  return ret;
}

void run() {
  scanf("%d%d%d%d%d", &n, &D[0], &C[0], &D[1], &C[1]);
  for (int i = 0; i < n; ++i) scanf("%d", cost + i);
  for (int i = 1; i < n; ++i) {
    int u, v; scanf("%d%d", &u, &v); --u, --v;
    G[u].push_back(v); G[v].push_back(u);
  }
  ans_t ret;
  for (int sep = 0; sep < n; ++sep) {
    for (auto &v: G[sep]) dfs1(v, sep, v);
    for (int g = 0; g < n; ++g) if (g != sep) {
      f[g][0] = solve(sep, g, D[0], C[0]); 
      f[g][1] = solve(sep, g, D[1], C[1]); 
    }
    for (int u = 0; u < n; ++u) {
      for (int v = 0; v < n; ++v) {
        if (bel[u] == bel[v] || u == sep || v == sep) continue;
        if (f[u][0].empty()) continue;
        if (f[v][1].empty()) continue;
        if (ret < f[u][0] + f[v][1]) ret = f[u][0] + f[v][1];
      }
    }
  }
  if (ret.empty()) puts("-1");
  else {
    int sum = accumulate(cost, cost + n, 0);
    printf("%d\n", sum - ret.sum);
    for (int i = 0; i < n; ++i) if (ret.u[i] == 0) {
      printf("%d ", i + 1);
    }
    puts("");
  }
}

int main() {
  run();
  return 0;
}
