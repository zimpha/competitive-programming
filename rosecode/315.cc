#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

inline pair<ll,ll> bezout(ll a, ll b) {
  ll xp=1,yp=0,dp=a,x=0,y=1,d=b;
  for (; dp%d; ) {
    ll k=dp/d,xn=xp-k*x,yn=yp-k*y,dn=dp%d;
    xp=x,x=xn,yp=y,y=yn,dp=d,d=dn;
  }
  if (d!=1)
    fprintf(stderr,"No solution for Bezout identity %lldx + %lldy = 1 because gcf is %lld > 1\n",a,b,d),abort();
  return pair<ll,ll>(x,y);
}

inline ll invMod(ll a, ll mod) {
  return (bezout(a,mod).first+mod)%mod;
}

inline ll gcf(ll x, ll y) {
  if (!y)
    return x;
  for (ll r; (r=x%y); x=y,y=r);
  return y;
}

int main(int argc, char* argv[]) {
  ll r=(argc<2?1:atoll(argv[1]));

  ll *X=new ll[r+1], *Y=new ll[r+1], np=0;
  for (ll x=0,y=r; x<=r; x++) {
    for (;x*x+y*y>r*r;y--);
    if (r*r-x*x-y*y<10000)X[np]=x,Y[np++]=y;
  }
  //printf("Considering %lld points.\n",np);

  ld pmax=0, R;
  ll ret = 0;
  for (ll i=0; i<np; i++)
    for (ll j=0; j<np; j++) {
      ll dxAB=X[i]+X[j], dyAB=Y[i]+Y[j];
      if (gcf(dxAB,dyAB)>1)continue;
      ll dxAC=(dxAB==1?0:dxAB-invMod(dyAB,dxAB)), dyAC=(dyAB*dxAC+1)/dxAB;
      ll dxBC=dxAB-dxAC, dyBC=dyAB-dyAC;
      ld a=sqrtl(dxBC*dxBC+dyBC*dyBC), b=sqrtl(dxAC*dxAC+dyAC*dyAC), c=sqrtl(dxAB*dxAB+dyAB*dyAB), p=a+b+c;
      if (p>pmax) {
        pmax=p,R=(ld)a*b*c/2;//,printf("(dx,dy)=(%lld,%lld), (dxAC,dyAC)=(%lld,%lld), a=%Lf, b=%Lf, c=%Lf, p=%Lf, R=%Lf\n",dx,dy,dxAC,dyAC,a,b,c,p,R);
        ret=dxBC*dxBC+dyBC*dyBC;
        ret += dxAC*dxAC+dyAC*dyAC;
        ret += dxAB*dxAB+dyAB*dyAB;
      }
    }
  std::cout << ret << std::endl;
}
