// http://www.spoj.com/problems/BOI7ESC/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN=600,MAXM=500000,inf=1e9;

namespace NetFlow {
  struct Edge {
    int v,c,f,n;
    Edge() {}
    Edge(int v,int c,int f,int n):v(v),c(c),f(f),n(n){}
  } E[MAXM];
  int G[MAXN],cur[MAXN],pre[MAXN],dis[MAXN],gap[MAXN];
  int N,S,T,sz;
  void init(int _n,int _s,int _t){
    N=_n,S=_s,T=_t; sz=0;
    memset(G,-1,sizeof(G));
  }
  void link(int u,int v,int c) {
    E[sz]=Edge(v,c,0,G[u]); G[u]=sz++;
    E[sz]=Edge(u,0,0,G[v]); G[v]=sz++;
  }
  int ISAP() {
    int maxflow=0,aug=inf,u,v;
    for (int i=0;i<=N;++i)cur[i]=G[i],gap[i]=dis[i]=0;
    for(gap[S]=N,u=pre[S]=S;dis[S]<N;){
      bool flag=false;
      for (int &h=cur[u];~h;h=E[h].n) {
        if(E[h].c>E[h].f&&dis[u]==dis[v=E[h].v]+1) {
          if(E[h].c-E[h].f<aug)aug=E[h].c-E[h].f;
          pre[v]=u,u=v; flag=true;
          if (u==T) {
            for (maxflow+=aug;u!= S;) {
              E[cur[u=pre[u]]].f+=aug;
              E[cur[u]^1].f-= aug;
            }
            aug=inf;
          }
          break;
        }
      }
      if (flag) continue;
      int mindis=N;
      for (int h=G[u];~h;h=E[h].n) {
        if (E[h].c>E[h].f&&dis[E[h].v]<mindis) {
          mindis=dis[E[h].v]; cur[u]=h;
        }
      }
      if ((--gap[dis[u]])==0) break;
      ++gap[dis[u]=mindis+1]; u=pre[u];
    }
    return maxflow;
  }
}

int x[MAXN], y[MAXN];
int L, W, N;

LL sqr(LL x) {return x * x;}
bool inter(int a, int b) {return sqr(x[a] - x[b]) + sqr(y[a] - y[b]) <= sqr(200);}
bool upper(int a) {return W - y[a] <= 100;}
bool lower(int a) {return y[a] <= 100;}

int main() {
  scanf("%d%d%d", &L, &W, &N);
  for (int i = 0; i < N; ++ i) {
    scanf("%d%d", x + i, y + i);
  }
  NetFlow::init(N * 2 + 10, N * 2, N * 2 + 1);
  for (int i = 0; i < N; ++ i) {
    if (upper(i)) NetFlow::link(NetFlow::S, 2 * i, inf);
    if (lower(i)) NetFlow::link(2 * i + 1, NetFlow::T, inf);
    NetFlow::link(i * 2, i * 2 + 1, 1);
    for (int j = 0; j < N; ++ j) if (i != j) {
      if (inter(i, j)) NetFlow::link(i * 2 + 1, j * 2, inf);
    }
  }
  printf("%d\n", NetFlow::ISAP());
  return 0;
}
