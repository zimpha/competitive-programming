#include <cstdio>
#include <cassert>
#include <vector>
#include <set>
#include <cstring>
#include <algorithm>

static const int N = 1e6 + 1e3 + 10; // 最大的单侧点个数

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

struct Tarjan {// index from 0 to n - 1
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
      ++scc_cnt;
      do {
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

std::vector<int> edges[N];

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  if (m == 1) {
    puts("0");
    return 0;
  }
  std::vector<std::vector<bool>> drill(n, std::vector<bool>(m));
  for (int i = 0; i < q; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    drill[x - 1][y - 1] = 1;
  }
  for (int i = 0; i < n; ++i) {
    edges[i].reserve(m);
    for (int j = 0; j < m; ++j) {
      if (!drill[i][j]) edges[i].push_back(j);
    }
  }
  int cnt = hk.gao(n, edges);
  if (cnt != m) {
    printf("%d\n", n * m - q);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (!drill[i][j]) printf("%d %d\n", i + 1, j + 1);
      }
    }
    return 0;
  }
  int s = n + m, t = n + m + 1;
  for (int i = 0; i < n + m + 2; ++i) {
    edges[i].clear();
    if (i < n) edges[i].reserve(m);
    else edges[i].reserve(n);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (drill[i][j]) continue;
      if (hk.pos[i] == j) edges[j + n].push_back(i);
      else edges[i].push_back(j + n);
    }
  }
  for (int i = 0; i < n; ++i) {
    if (hk.pos[i] != -1) edges[i].push_back(s);
    else edges[s].push_back(i);
  }
  for (int i = 0; i < m; ++i) {
    if (hk.neg[i] != -1) edges[t].push_back(i + n);
    else edges[i + n].push_back(t);
  }
  scc.run(n + m + 2, edges);
  std::vector<std::pair<int, int>> ret;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (drill[i][j]) continue;
      if (scc.col[i] != scc.col[j + n] && hk.pos[i] != j) ret.emplace_back(i, j);
    }
  }
  printf("%d\n", (int)ret.size());
  for (auto &e: ret) {
    printf("%d %d\n", e.first + 1, e.second + 1);
  }
  return 0;
}
