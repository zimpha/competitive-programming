#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;

//ax+by=gcd(a,b),|x|+|y|is minimum
void exgcd(LL a,LL b,LL &g,LL &x,LL &y) {
  if (!b) x=1,y=0,g=a;
  else {exgcd(b,a%b,g,y,x);y-=x*(a/b);}
}
LL ceil(LL a, LL b) {
  return ceil(1.0 * a / b);
}
LL floor(LL a, LL b) {
  return floor(1.0 * a / b);
}
LL solve(LL a,LL b,LL c, LL x1, LL x2, LL y1, LL y2) {
  if (c < 0) a = -a, b = - b, c = -c;
  if (a < 0) a = -a, swap(x1, x2), x1 = -x1, x2 = -x2;
  if (b < 0) b = -b, swap(y1, y2), y1 = -y1, y2 = -y2;
  if (b == 0 && a != 0) return c % a == 0 && x1 <= c / a && c / a <= x2 ? y2 - y1 + 1 : 0;
  if (b != 0 && a == 0) return c % b == 0 && y1 <= c / b && c / b <= y2 ? x2 - x1 + 1 : 0;
  if (a == 0 && b == 0) return c == 0 ? (y2 - y1 + 1) * (x2 - x1 + 1) : 0;
  LL g, x, y;
  exgcd(a,b,g,x,y);
  if (c % g) return false;
  b /= g; a /= g; c /= g;
  x *= c; y *= c; //xx=x+tb,yy=y-ta
  // x1 <= x + tb <= x2, y1 <= y - ta <= y2
  LL l = max(ceil(x1 - x, b), ceil(y - y2, a));
  LL r = min(floor(x2 - x, b), floor(y - y1, a));
  return l <= r ? r - l + 1 : 0;
}

int main() {
  LL a, b, c;
  cin >> a >> b >> c;
  LL x1, x2, y1, y2;
  cin >> x1 >> x2;
  cin >> y1 >> y2;
  cout << solve(a, b, -c, x1, x2, y1, y2) << endl;
  return 0;
}
