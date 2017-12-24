#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef unsigned long long ll;
const int N=300010,M=16,E=700000 * 3;
const ll inf=~0ULL;
int n,m,type,last,i,x,y,k,A,B,a[N],b[N],g[N],v[N<<1],nxt[N<<1],ok[N<<1],ed;
int son[N],f[N],all,now,mx,dep[N];
struct P{int x,y,d,o;P(){}P(int _x,int _y,int _d,int _o){x=_x,y=_y,d=_d,o=_o;}};
inline bool cmp(const P&a,const P&b){return a.x<b.x;}
vector<P>G[N];
int q[M],cnt,cur[4],pos[E][4];ll pool[E][4],bit[M];
inline void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
inline void add(int x,int y){v[++ed]=y;nxt[ed]=g[x];g[x]=ed;ok[ed]=1;}
void findroot(int x,int y){
  son[x]=1;f[x]=0;
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y){
    findroot(v[i],x);
    son[x]+=son[v[i]];
    if(son[v[i]]>f[x])f[x]=son[v[i]];
  }
  if(all-son[x]>f[x])f[x]=all-son[x];
  if(f[x]<f[now])now=x;
}
void cald(int x,int y,int z){
  dep[x]=z;
  if(z>mx)mx=z;
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)cald(v[i],x,z+1);
}
void dfs1(int x,int y,int z){
  if(y==now)z=x;
  int t=cur[b[x]>>2];
  cur[b[x]>>2]=++cnt;
  for(int i=0;i<4;i++)pool[cnt][i]=pool[t][i];
  pool[cnt][b[x]&3]|=1ULL<<(a[x]&63);
  for(int i=0;i<4;i++)pos[cnt][i]=cur[i];
  G[x].push_back(P(now,z,dep[x],cnt));
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)dfs1(v[i],x,z);
  cur[b[x]>>2]=t;
}
void dfs2(int x,int y,int z){
  if(y==now)z=x;
  G[x].push_back(P(now,z,dep[x],0));
  for(int i=g[x];i;i=nxt[i])if(ok[i]&&v[i]!=y)dfs2(v[i],x,z);
}
void solve(int x){
  mx=0;
  cald(x,0,0);
  if(mx>M)dfs1(x,0,0);else dfs2(x,0,0);
  for(int i=g[x];i;i=nxt[i])if(ok[i]){
    ok[i^1]=0;
    f[0]=all=son[v[i]];
    findroot(v[i],now=0);
    solve(now);
  }
}
void dfs3(int x,int y){
  dep[x]=dep[y]+1;f[x]=y;
  for(int i=g[x];i;i=nxt[i])if(v[i]!=y)dfs3(v[i],x);
}
inline void visit(int x){
  x=a[x];
  bit[x>>6]|=1ULL<<(x&63);
}
inline void chain(int x,int y,int d,int o){
  if(d>M){
    for(int i=0;i<4;i++)for(int j=0,k=pos[o][i];j<4;j++)bit[i<<2|j]|=pool[k][j];
    return;
  }
  while(x!=y){
    if(dep[x]<dep[y])swap(x,y);
    visit(x);
    x=f[x];
  }
  visit(x);
}
inline void work(int x,int y){
  if(x==y){visit(x);return;}
  vector<P>::iterator i=G[x].begin(),j=G[y].begin();
  while(i!=G[x].end()&&j!=G[y].end()){
    if(i->x<j->x){i++;continue;}
    if(i->x>j->x){j++;continue;}
    if(i->y==j->y){i++,j++;continue;}
    if(i->x!=x)chain(x,i->x,i->d,i->o);
    if(i->x!=y)chain(y,j->x,j->d,j->o);
    i++,j++;
  }
}
inline int ask(){
  int ret=0;
  for(int i=0;i<M;i++)ret+=__builtin_popcountll(bit[i]);
  return ret;
}

int main(){
  read(n),read(k),read(m);
  ed=1;
  for (int i = 2; i <= n; ++i) {
    int p;
    read(p);
    add(p + 1, i);
    add(i, p + 1);
  }
  for(i=1;i<=n;i++) {
    read(a[i]);
    b[i]=a[i]>>6;
  }
  f[0]=all=n;findroot(1,now=0);solve(now);
  for(i=1;i<=n;i++)sort(G[i].begin(),G[i].end(),cmp);
  dfs3(1,0);
  while(m--){
    k=3;
    for(i=0;i<M;i++)bit[i]=0;
    while(k--){
      read(x),read(y);
      work(x+1,y+1);
    }
    A=ask();
    printf("%d\n",A);
  }
  return 0;
}
