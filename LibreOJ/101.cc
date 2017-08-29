#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using ll = long long;

namespace NetFlow {
  const int N=1e6 + 10,MAXM=8e6 + 10;
  const ll inf = 1e18;
  struct Edge {
    int v, nx;//c:capcity, f:flow
    ll c, f;
    Edge() {}
    Edge(int v,ll c,ll f,int nx):v(v),c(c),f(f),nx(nx) {}
  } E[MAXM];
  int G[N],cur[N],pre[N],dis[N],gap[N],n,sz;
  void init(int _n) {
    n=_n,sz=0;
    memset(G,-1,sizeof(*G)*n);
  }
  void link(int u,int v,int c) {
    E[sz]=Edge(v,c,0,G[u]); G[u]=sz++;
    E[sz]=Edge(u,0,0,G[v]); G[v]=sz++;
  }
  ll ISAP(int S,int T) {//S -> T
    ll maxflow=0,aug=inf;
    int flag=false,u,v;
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
    static int Q[N];
    memset(dis,-1,sizeof(*dis)*n);
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
  ll dfs(int u,int T,ll low) {
    if (u==T) return low;
    ll ret=0,tmp,v;
    for (int &it=cur[u];~it&&ret<low;it=E[it].nx) {
      if (dis[v=E[it].v]==dis[u]+1&&E[it].c>E[it].f) {
        if (tmp=dfs(v,T,std::min(low-ret,E[it].c-E[it].f))) {
          ret+=tmp; E[it].f+=tmp; E[it^1].f-=tmp;
        }
      }
    }
    if (!ret) dis[u]=-1; return ret;
  }
  ll dinic(int S,int T) {
    ll maxflow=0,tmp;
    while (bfs(S,T)) {
      memcpy(cur,G,sizeof(G[0])*n);
      while (tmp=dfs(S,T,inf)) maxflow+=tmp;
    }
    return maxflow;
  }
}

int main() {
  int n, m, s, t;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  NetFlow::init(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    NetFlow::link(u - 1, v - 1, w);
  }
  printf("%lld\n", NetFlow::ISAP(s - 1, t - 1));
  return 0;
}
