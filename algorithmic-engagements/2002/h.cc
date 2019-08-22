#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <functional>
#include <algorithm>

static const int N = 20005; // 最大的单侧点个数

class Hopcroft {
public:
  int cnt,pos[N],neg[N]; // pos[]为左侧点所匹配到的右侧点编号
  // neg[]反之，没有匹配到对应的点则为-1
  // 传入左侧点个数n和左侧点至右侧点的边表e[]，返回匹配点对的数量cnt
  int gao(int n, const std::vector<int> e[]){ // 复杂度O(sqrt(n)*m)
    std::fill(pos,pos+n,-1);
    std::fill(neg,neg+n,-1);
    for(int x=cnt=0,y;x<n;x++){
      for(size_t i=0;i<e[x].size();i++){
        if(~neg[y=e[x][i]]) continue;
        pos[neg[y]=x]=y;
        cnt++; break;
      }
    }
    while(true){
      int push=0,pop=0,ok=0;
      std::fill(lx,lx+n,-1);
      std::fill(ly,ly+n,-1);
      for(int x=0;x<n;x++) if(pos[x]<0) lx[q[push++]=x]=0;
      while(push!=pop){
        int x=q[pop++],y;
        for(size_t i=0;i<e[x].size();i++){
          if(~ly[y=e[x][i]]) continue;
          ly[y]=1+lx[x];
          if(~neg[y] && ~lx[neg[y]]) continue;
          if(~neg[y]) lx[q[push++]=neg[y]]=1+ly[y];
          else ok=1;
        }
      }
      if(!ok) return cnt;
      for(int x=0;x<n;x++) if(pos[x]<0 && aug(x,e)) cnt++;
    }
  }
private:
  int lx[N],ly[N],q[N];
  bool aug(int x, const std::vector<int> e[]){
    int c=lx[x]+1,y=lx[x]=-1;
    for(size_t i=0;i<e[x].size();i++) if(ly[y=e[x][i]]==c){
      ly[y]=-1;
      if(~neg[y] && !aug(neg[y],e)) continue;
      pos[neg[y]=x]=y;
      return true;
    }
    return false;
  }
} hk;

std::vector<int> edges[N];
std::vector<int> edges2[N];

struct Tarjan {// index from 0 to n - 1
  std::vector<int> SCC[N];
  int low[N], dfn[N], col[N];
  int stk[N], top, scc_cnt, sz;
  void dfs(int x, const std::vector<int> G[]) {
    low[x] = dfn[x] = ++sz;
    stk[++top] = x;
    for (auto &y: G[x]) {
      if (!dfn[y]) {
        dfs(y, G);
        low[x] = std::min(low[x], low[y]);
      }
      else if (col[y] == -1) {
        low[x] = std::min(low[x], dfn[y]);
      }
    }
    if (dfn[x] == low[x]) {
      SCC[scc_cnt++].clear();
      do {
        SCC[scc_cnt - 1].push_back(stk[top]);
        col[stk[top]] = scc_cnt - 1;
      } while (stk[top--] != x);
    }
  }
  void run(int n,const std::vector<int> G[]) {
    sz = top = scc_cnt = 0;
    memset(dfn,  0, sizeof(*dfn) * n);
    memset(col, -1, sizeof(*col) * n);
    for (int i = 0; i < n; ++i) {
      if (!dfn[i]) dfs(i,G);
    }
  }
} scc;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[u].push_back(v);
  }
  int cnt = hk.gao(n, edges);
  if (cnt != n) {
    puts("NIE");
  } else {
    for (int i = 0; i < n; ++i) {
      for (auto &j: edges[i]) {
        if (hk.pos[i] == j) edges2[i].push_back(j + n);
        else edges2[j + n].push_back(i);
      }
    }
    scc.run(n * 2, edges2);
    int cnt = 0;
    for (int i = 0; i < scc.scc_cnt; ++i) {
      cnt += scc.SCC[i].size() > 1;
    }
    int ret = 1;
    for (int i = 0; i < cnt; ++i) {
      ret = ret * 2 % 10000;
    }
    printf("%d\n", ret);
  }
  return 0;
}
