#include <cstring>
#include <cstdio>
#include <vector>

const int N = 500, inf = 1e9;
int a[N], b[N], w[N][N];
int perm[N], buffer[N];

int edmonds(int n, int G[][N], int pre[]) {
  static int vis[N][N], l[N], p[N];
  int m=n,cnt,ret=0;
  for (int i=0;i<n;++i) l[i]=i;
  do {
    memset(vis,0,sizeof(vis));
    memset(p,0xff,sizeof(p));
    cnt=m; for (int i=0;i<m;++i) vis[i][i]=1;
    for (int i=0;i<cnt;++i) if (l[i]==i&&pre[i]!=-1) {
      for (int j=0;j<m;++j) {
        if (l[j]==j&&i!=j&&G[j][i]<inf&&(p[i]==-1||G[j][i]<G[p[i]][i])) p[i]=j;
      }
      if ((pre[i]=p[i])==-1) return -1;
      if (vis[i][p[i]]) {
        for (int j=0;j<=m;++j) G[j][m]=G[m][j]=inf;
        for (int k=i;l[k]!=m;l[k]=m,k=p[k]) 
          for (int j=0;j<m;++j) if (l[j]==j) {
            if (G[j][k]-G[p[k]][k]<G[j][m]) G[j][m]=G[j][k]-G[p[k]][k];
            if (G[k][j]<G[m][j]) G[m][j]=G[k][j];
          }
        vis[m][m]=1; l[m]=m; m++;
      }
      for (int j=0;j<m;++j) if (vis[i][j]) {
        for (int k=p[i];k!=-1&&l[k]==k; k=p[k]) vis[k][j]=1;
      }
    }
  } while (cnt<m);
  for (int k;m-->n;pre[k]=pre[m]) {
    for (int i=0;i<m;++i) if (l[i]==m) {
      for (int j=0;j<m;++j)
        if (pre[j]==m&&G[i][j]==G[m][j]) pre[j]=i;
      if (G[pre[m]][m]==G[pre[m]][i]-G[pre[i]][i]) k=i;
    }
  }
  for (int i=0;i<n;++i) if (pre[i]!=-1) ret+=G[pre[i]][i];
  return ret;
}

// prefix of length m is fixed
int cost(int *perm, int n, int m) {
  std::vector<int> used(n), idx(n);
  int ret = 0;
  for (int i = 0; i < m; ++i) {
    used[perm[i]] = 1;
    int now = a[perm[i]] ^ b[perm[i]];
    for (int j = 0; j < i; ++j) {
      now = std::min(now, a[perm[i]] ^ b[perm[j]]);
    }
    ret += now;
  }
  int size = 1;
  for (int i = 0; i < n; ++i) {
    if (!used[i]) idx[i] = size++;
  }
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      w[i][j] = inf;
    }
  }
  for (int i = 0; i < n; ++i) if (!used[i]) {
    w[0][idx[i]] = std::min(w[0][idx[i]], a[i] ^ b[i]);
    for (int j = 0; j < n; ++j) {
      if (used[j]) {
        w[0][idx[i]] = std::min(w[0][idx[i]], a[i] ^ b[j]);
      } else {
        w[idx[j]][idx[i]] = a[i] ^ b[j];
      }
    }
  }
  for (int i = 0; i < size; ++i) buffer[i] = 0;
  buffer[0] = -1;
  return ret + edmonds(size, w, buffer);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  for (int i = 0; i < n; ++i) scanf("%d", &b[i]);
  int best = cost(perm, n, 0);
  std::vector<int> used(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (used[j]) continue;
      perm[i] = j;
      if (best == cost(perm, n, i + 1)) break;
    }
    used[perm[i]] = 1;
  }
  printf("%d\n", best);
  for (int i = 0; i < n; ++i) {
    if (i) putchar(' ');
    printf("%d", perm[i] + 1);
  }
  puts("");
  return 0;
}
