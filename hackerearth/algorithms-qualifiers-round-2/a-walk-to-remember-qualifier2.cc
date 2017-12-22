#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 100000 + 10;

struct Tarjan {// index from 0 to n - 1
  vector<int> SCC[MAXN];
  int low[MAXN],dfn[MAXN],stk[MAXN],col[MAXN];
  int scc_cnt,sz,top;
  void dfs(int x,const vector<int> G[]) {
    low[x]=dfn[x]=++sz; stk[++top]=x;
    for (int i=0,y;i<(int)G[x].size();++i) {
      if (!dfn[y=G[x][i]]) {
        dfs(y,G); low[x]=min(low[x],low[y]);
      }
      else if (col[y]==-1) low[x]=min(low[x],dfn[y]);
    }
    if (dfn[x]==low[x]) {
      SCC[scc_cnt++].clear();
      do {
        SCC[scc_cnt-1].push_back(stk[top]);
        col[stk[top]]=scc_cnt-1;
      } while (stk[top--]!= x);
    }
  }
  void solve(int n,const vector<int> G[]) {
    sz=top=scc_cnt=0; memset(dfn,0,sizeof(dfn));
    memset(col,-1,sizeof(col));
    for (int i=0;i<n;++i) if (!dfn[i]) dfs(i,G);
  }
} scc;

vector<int> G[MAXN];
int n, m;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++ i) {
    int u, v; scanf("%d%d", &u, &v);
    G[-- u].push_back(-- v);
  }
  scc.solve(n, G);
  for (int i = 0; i < n; ++ i) {
    int c = scc.col[i];
    if (i) putchar(' ');
    if (scc.SCC[c].size() > 1) putchar('1');
    else putchar('0');
  }
  puts("");
  return 0;
}
