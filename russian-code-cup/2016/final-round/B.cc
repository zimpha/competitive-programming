#include <cstdio>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>

namespace NetFlow {
  const int N=100000,MAXM=200000,inf=1e9;
  struct Edge {
    int v,c,f,nx;//c:capcity, f:flow
    Edge() {}
    Edge(int v,int c,int f,int nx):v(v),c(c),f(f),nx(nx) {}
  } E[MAXM];
  int G[N],cur[N],pre[N],dis[N],gap[N],n,sz;
  void init(int _n) {
    n=_n,sz=0; memset(G,-1,sizeof(G[0])*n);
  }
  void link(int u,int v,int c) {
    E[sz]=Edge(v,c,0,G[u]); G[u]=sz++;
    E[sz]=Edge(u,0,0,G[v]); G[v]=sz++;
  }
  int ISAP(int S,int T) {//S -> T
    int maxflow=0,aug=inf,flag=false,u,v;
    for (int i=0;i<n;++i)cur[i]=G[i],gap[i]=dis[i]=0;
    for (gap[S]=n,u=pre[S]=S;dis[S]<n;flag=false) {
      for (int &it=cur[u];~it;it=E[it].nx) {
        if (E[it].c>E[it].f&&dis[u]==dis[v=E[it].v]+1) {
          if (aug>E[it].c-E[it].f) aug=E[it].c-E[it].f;
          pre[v]=u,u=v; flag=true;
          if (u==T) {
            for (maxflow+=aug;u!=S;) {
              E[cur[u=pre[u]]].f+=aug;
              E[cur[u]^1].f-=aug;
            }
            aug=inf;
          }
          break;
        }
      }
      if (flag) continue;
      int mx=n;
      for (int it=G[u];~it;it=E[it].nx) {
        if (E[it].c>E[it].f&&dis[E[it].v]<mx) {
          mx=dis[E[it].v]; cur[u]=it;
        }
      }
      if ((--gap[dis[u]])==0) break;
      ++gap[dis[u]=mx+1]; u=pre[u];
    }
    return maxflow;
  }
  bool bfs(int S,int T) {
    static int Q[N]; memset(dis,-1,sizeof(dis[0])*n);
    dis[S]=0; Q[0]=S;
    for (int h=0,t=1,u,v,it;h<t;++h) {
      for (u=Q[h],it=G[u];~it;it=E[it].nx) {
        if (dis[v=E[it].v]==-1&&E[it].c>E[it].f) {
          dis[v]=dis[u]+1; Q[t++]=v;
        }
      }
    }
    return dis[T]!=-1;
  }
  int dfs(int u,int T,int low) {
    if (u==T) return low;
    int ret=0,tmp,v;
    for (int &it=cur[u];~it&&ret<low;it=E[it].nx) {
      if (dis[v=E[it].v]==dis[u]+1&&E[it].c>E[it].f) {
        if (tmp=dfs(v,T,std::min(low-ret,E[it].c-E[it].f))) {
          ret+=tmp; E[it].f+=tmp; E[it^1].f-=tmp;
        }
      }
    }
    if (!ret) dis[u]=-1; return ret;
  }
  int dinic(int S,int T) {
    int maxflow=0,tmp;
    while (bfs(S,T)) {
      memcpy(cur,G,sizeof(G[0])*n);
      while (tmp=dfs(S,T,inf)) maxflow+=tmp;
    }
    return maxflow;
  }
}

const int N = 10000 + 10;

struct edge_t {
  int u, v, c, used;
  int to(int x) {return u + v - x;}
} E[N * 3];

std::map<std::pair<int, int>, int> edge_id;
std::vector<int> edges[N];
int vis[N], dep[N], pre[N];
int S, T, n, m, sz;

int get_edge(int u, int v) {
  if (u > v) std::swap(u, v);
  return edge_id[std::make_pair(u, v)];
}

void dfs(int u, int d = 0, int f = -1) {
  if (vis[u]) {
    if (d > dep[u]) {
      std::vector<int> cyc = {u};
      for (int v = f; v != u; v = pre[v]) {
        cyc.push_back(v);
      }
      int cnt = cyc.size();
      cyc.push_back(u);
      NetFlow::link(S, sz + m, cnt - 1);
      for (size_t i = 0; i < cnt; ++i) {
        int a = cyc[i], b = cyc[i + 1];
        int p = get_edge(a, b);
        E[p].used = true;
        NetFlow::link(sz + m, E[p].c, 1);
      }
      sz++;
    }
    return;
  }
  dep[u] = d;
  vis[u] = true;
  pre[u] = f;
  for (auto &&x: edges[u]) {
    if (E[x].to(u) != f) dfs(E[x].to(u), d + 1, u);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].c);
    --E[i].c;
    --E[i].u;
    --E[i].v;
    if (E[i].u > E[i].v) std::swap(E[i].u, E[i].v);
    edge_id[std::make_pair(E[i].u, E[i].v)] = i;
    E[i].used = false;
    edges[E[i].u].push_back(i);
    edges[E[i].v].push_back(i);
  }
  S = m * 2, T = m * 2 + 1, sz = 0;
  NetFlow::init(T + 1);
  dfs(0);
  for (int i = 0; i < m; ++i) {
    NetFlow::link(i, T, 1);
    if (!E[i].used) {
      NetFlow::link(S, sz + m, 1);
      NetFlow::link(sz + m, E[i].c, 1);
      sz++;
    }
  }
  printf("%d\n", NetFlow::ISAP(S, T));
  return 0;
}
