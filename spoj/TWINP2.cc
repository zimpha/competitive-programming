#include<cstdio>

const int N=18409201,M=100000;

bool v[N+1];
int tw[M],cnt;
int p[10000],m;

void prepare(){
int last=-1,cnt=m=0;
for(int i=2;i<=N;++i){
if(!v[i]){
if(i<=N/i)p[m++]=i;
if(i-last==2)tw[cnt++]=last;
last=i;
}
for(int j=0,u=N/i;j<m&&p[j]<=u;++j){
v[p[j]*i]=1;
if(i%p[j]==0)break;
}
}
}

int main(){
prepare();
int T;
scanf("%d",&T);
for(int _=1;_<=T;++_){
int n;
scanf("%d",&n);
printf("%d %d\n",tw[n-1],tw[n-1]+2);
}
return 0;
}
