#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int N = 51;

struct KM {
  typedef int cost_t;
  static const int MAXN = 51;
  static const cost_t inf = 1e9;
  cost_t lx[MAXN], ly[MAXN], sl[MAXN];
  int px[MAXN],py[MAXN],sy[MAXN],fa[MAXN],n;
  void aug(int v) {
    sy[v]=py[v]; if (px[sy[v]]!=-2) aug(px[sy[v]]);
  }
  bool find(int v, const cost_t w[][MAXN]) {
    for (int i=0;i<n;++i) if (!~py[i]) {
      if (sl[i]>lx[v]+ly[i]-w[v][i]) {
        sl[i]=lx[v]+ly[i]-w[v][i]; fa[i] = v;
      }
      if (lx[v]+ly[i]==w[v][i]) {
        py[i]=v; if (!~sy[i]) {aug(i); return 1;}
        if (~px[sy[i]]) continue;
        px[sy[i]]=i; if (find(sy[i],w)) return 1;
      }
    }
    return 0;
  }
  cost_t gao(int _n, const cost_t w[][MAXN], cost_t m=inf) {
    n=_n; std::fill(sy,sy+n,-1); std::fill(ly,ly+n,0);
    for (int i=0;i<n;++i) lx[i]=*std::max_element(w[i],w[i]+n);
    for (int i(0),flag;i<n;++i) {
      for (int j=0;j<n;++j)px[j]=py[j]=-1,sl[j]=inf;
      px[i]=-2; if (find(i,w)) continue;
      for (flag=0,m=inf; !flag; m=inf) {
        for (int j=0;j<n;++j) if (!~py[j]) m=std::min(m,sl[j]);
        for (int j=0;j<n;++j) {
          if (~px[j]) lx[j]-=m;
          if (~py[j]) ly[j]+=m;
          else sl[j]-=m;
        }
        for (int j=0;j<n;++j) if (!~py[j]&&!sl[j]) {
          py[j]=fa[j]; if (!~sy[j]) {aug(j);flag=1;break;}
          px[sy[j]]=j; if (find(sy[j],w)) {flag=1;break;}
        }
      }
    }
    cost_t ret(0);
    for (int i=0;i<n;++i) ret+=w[sy[i]][i];
    return ret;
  }
} km;

std::vector<int> ga[N], gb[N];
int w[N][N];
int dp[N][N][N][N];
int n, m;

int solve(int u, int pu, int v, int pv) {
  if (dp[pu][u][pv][v]) return dp[pu][u][pv][v];
  int ret = 1;
  for (auto &&x: ga[u]) for (auto &&y: gb[v]) {
    if (x == pu || y == pv) continue;
    solve(x, u, y, v);
  }
  memset(w, 0, sizeof(w));
  for (auto &&x: ga[u]) for (auto &&y: gb[v]) {
    if (x == pu || y == pv) continue;
    w[x][y] = solve(x, u, y, v);
  }
  ret += km.gao(std::max(n, m), w);
  return dp[pu][u][pv][v] = ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    ga[u - 1].push_back(v - 1);
    ga[v - 1].push_back(u - 1);
  }
  scanf("%d", &m);
  for (int i = 1; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    gb[u - 1].push_back(v - 1);
    gb[v - 1].push_back(u - 1);
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ret = std::max(ret, solve(i, i, j, j));
    }
  }
  printf("%d\n", ret);
  return 0;
}
