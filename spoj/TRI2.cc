#include <cstdio>
const int N=5e6+10,m=1e9+7;
int f[N],g[N],p[N];
void h() {
 p[1]=f[3]=1;
 for(int i=2;i<N;++i)p[i]=(p[i-1]*2)%m;
 for(int i=4;i<N;++i){
  f[i]=f[i-1]+(i-1)/2-i/3+(i%3?0:1);
  if(!(i&1))f[i]-=i/4;
  f[i]=(f[i]+m)%m;
 }
 for(int i=3;i<N;++i){
  g[i]=(g[i]+f[i])%m;
  for(int j=i+i;j<N;j+=i){
   g[j]=(g[j]+1ll*f[i]*p[j/i])%m;
   f[j]=(f[j]-f[i]+m)%m;
  }
 }
}
int main() {
 h();
 for(int n,c=0;scanf("%d",&n)==1;) {
  printf("Case %d: %d\n",++c,g[n]);
 }
 return 0;
}
