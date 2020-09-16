#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 20000 + 10;

int sum[16][N][26];
int cnt[16][26];
int cost[26][26];
char s[N];

struct KM {
  using cost_t = int;
  static const int N = 26;
  static const cost_t inf = 1e9;
  cost_t lx[N], ly[N], sl[N];
  int px[N],py[N],sy[N],fa[N],n;
  void aug(int v) {
    sy[v]=py[v]; if (px[sy[v]]!=-2) aug(px[sy[v]]);
  }
  bool find(int v, const cost_t w[][N]) {
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
  cost_t gao(int _n, const cost_t w[][N], cost_t m=inf) {
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
    for (int i=0;i<n;++i) ret+=w[sy[i]][i], px[sy[i]] = i;
    return ret;
  }
} km;

int main() {
  freopen("matching.in", "r", stdin);
  freopen("matching.out", "w", stdout);
  scanf("%s", s);
  int n = strlen(s);
  for (int l = 0; l < 16; ++l) {
    int w = 1 << l;
    for (int i = 0; i < n; ++i) {
      sum[l][i % w][s[i] - 'a']++;
    }
  }
  // center at p
  int best = -1, start = -1;
  int perm[26];
  for (int p = 0; p < n; ++p) {
    memset(cnt, 0, sizeof(cnt));
    for (int l = 0; l < 15; ++l) {
      int w = 1 << l;
      for (int c = 0; c < 26; ++c) {
        cnt[l][c] = sum[l][p % w][c] - sum[l + 1][p % (w * 2)][c];
      }
    }
    cnt[15][s[p] - 'a']++;
    memset(cost, 0, sizeof(cost));
    for (int i = 0; i < 16; ++i) {
      int total = 0;
      for (int j = 0; j < 26; ++j) total += cnt[i][j];
      for (int j = 0; j < 26; ++j) {
        if (i == 15) cost[25][j] = cnt[i][j] - total;
        else cost[i][j] = cnt[i][j] - total;
      }
    }
    int now = -km.gao(26, cost);
    if (best == -1 || best > now) {
      start = (1 << 25) - p;
      best = now;
      memcpy(perm, km.px, sizeof(perm));
    }
  }
  printf("%d\n%d\n", best, start);
  for (int i = 0; i < 26; ++i) putchar(perm[i] + 'a');
  puts("");
  return 0;
}
