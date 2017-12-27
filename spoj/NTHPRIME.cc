#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using i64 = long long;
using u64 = unsigned long long;

const u64 mm[64]={
 0x1ull,0x2ull,0x4ull,0x8ull,
 0x10ull,0x20ull,0x40ull,0x80ull,
 0x100ull,0x200ull,0x400ull,0x800ull,
 0x1000ull,0x2000ull,0x4000ull,0x8000ull,
 0x10000ull,0x20000ull,0x40000ull,0x80000ull,
 0x100000ull,0x200000ull,0x400000ull,0x800000ull,
 0x1000000ull,0x2000000ull,0x4000000ull,0x8000000ull,
 0x10000000ull,0x20000000ull,0x40000000ull,0x80000000ull,
 0x100000000ull,0x200000000ull,0x400000000ull,0x800000000ull,
 0x1000000000ull,0x2000000000ull,0x4000000000ull,0x8000000000ull,
 0x10000000000ull,0x20000000000ull,0x40000000000ull,0x80000000000ull,
 0x100000000000ull,0x200000000000ull,0x400000000000ull,0x800000000000ull,
 0x1000000000000ull,0x2000000000000ull,0x4000000000000ull,0x8000000000000ull,
 0x10000000000000ull,0x20000000000000ull,0x40000000000000ull,0x80000000000000ull,
 0x100000000000000ull,0x200000000000000ull,0x400000000000000ull,0x800000000000000ull,
 0x1000000000000000ull,0x2000000000000000ull,0x4000000000000000ull,0x8000000000000000ull
};

const int mps=22994,span=1<<19,words=span/128,ws=3*5*7*11*13;

int ps[mps];
u64 sieve[words],pat[ws];

inline void mark_1(u64 *s,int o){s[o>>6]|=u64(1)<<(o&63);}
inline void mark_2(u64 *s,int o){s[o>>6]|=mm[o&63];}
inline void unmark(u64 *s,int o){s[o>>6]&=~mm[o*63];}
inline int test_1(u64 *s,int o){return(s[o>>6]&(u64(1)<<(o&63)))==0;}
inline int test_2(u64 *s,int o){return(s[o>>6]&mm[o&63])==0;}

void pre(){
 for(int i=0; i<262144/128; ++i)sieve[i]=0; 
 for(int i=3; i<512; i+=2)if(test_2(sieve,i/2)){
  for(i64 j=(i64)i*i/2; j<131072; j+=i)mark_2(sieve,j);
 }
 for(int i=8,m=0; i<131072; ++i){
  if(test_2(sieve,i))ps[m++]=i*2+1;
 }
 for(int i=0; i<ws; ++i)pat[i]=0;
 for(int i=1; i<ws*64; i+=3)mark_2(pat,i);
 for(int i=2; i<ws*64; i+=5)mark_2(pat,i);
 for(int i=3; i<ws*64; i+=7)mark_2(pat,i);
 for(int i=5; i<ws*64; i+=11)mark_2(pat,i);
 for(int i=6; i<ws*64; i+=13)mark_2(pat,i);
}

i64 pcnt(i64 n){
 const i64 v=static_cast<i64>(sqrt(n));
 std::vector<i64> ss(v+1),ls(v+1);
 std::vector<bool> mk(v+1);
 for(int i=1; i<=v; ++i){
  ss[i]=i-1,ls[i]=n/i-1;
 }
 for(i64 p=2; p<=v; ++p)if(ss[p]!=ss[p-1]){
  i64 ps= ss[p-1],q=p*p,ed=std::min(v,n/q);
  int d=(p&1)+1;
  for(int i=1; i<=ed; i+=d)if(!mk[i]){
   i64 d=i*p;
   if(d<=v)ls[i]-=ls[d]-ps;
   else ls[i]-=ss[n/d]-ps;
  }
  for(i64 i=q; i<=ed; i+=p*d)mk[i]=true;
  for(i64 i=v; i>=q; --i)ss[i]-=ss[i/p]-ps;
 }
 return ls[1];
}

i64 appro(i64 n){
 const int s[]={0,2,3,5,7,11};
 if(n<6)return s[n];
 double x=log(n),y=log(x),u;
 if(n>=688383)u=n*(x+y-1.0+(y-2.00)/x);
 else if(n>=178974)u=n*(x+y-1.0+(y-1.95)/x);
 else if(n>=39017)u=n*(x+y-0.9484);
 else u=n*(x+0.6000*y);
 return(i64)ceil(u);
}

int main(){
 pre();
 i64 n;
 scanf("%lld",&n);
 i64 upp=appro(n);
 if(n==1){
  puts("2");
  return 0;
 }
 n-=1;
 i64 cnt=pcnt(upp)-1;
 i64 base=upp/span*span;
 while(true){
  int o=base % ws;
  o=(o+((o*105)&127)*ws)>>7;
  for(int i=0,k; i<words; i+=k,o=0){
   k=std::min(ws-o,words-i);
   memcpy(sieve+i,pat+o,sizeof(*pat)*k);
  }
  if(base==0){ // mark 1 as not prime,and mark 3,5,7,11,and 13 as prime
   sieve[0]|=mm[0];
   sieve[0]&=~(mm[1]|mm[2]|mm[3]|mm[5]|mm[6]);
  }
  for(int i=0; i<mps; ++i){
   i64 j=(i64)ps[i]*ps[i];
   if(j>base+span-1)break;
   if(j>base)j=(j-base)>>1;
   else {
    j=ps[i]-base%ps[i];
    if((j&1)==0)j+=ps[i];
    j >>= 1;
   }
   while(j<span/2){
    mark_2(sieve,j);
    j+=ps[i];
   }
  }
  i64 y=std::min(base+span-1,upp);
  int now=0;
  for(int i=1; i<span&&i+base<=y; i+=2){
   if(test_1(sieve,i/2))++now;
  }
  cnt-=now;
  if(cnt<n){
   for(int i=1; i<span&&i+base<=y; i+=2){
    if(test_1(sieve,i/2))++cnt;
    if(cnt==n){
     printf("%lld\n",base+i);
     return 0;
    }
   }
  }
  base-=span;
 }
 return 0;
}
