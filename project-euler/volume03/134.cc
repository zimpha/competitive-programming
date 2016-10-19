#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void exgcd(LL a,LL b,LL &g,LL &x,LL &y) {
  if (!b) x=1,y=0,g=a;
  else {exgcd(b,a%b,g,y,x);y-=x*(a/b);}
}

LL run(int n) {
  vector<int> pl, vs(n + 10, 0);
  for (int i = 2; i < n + 10; ++i) if (!vs[i]) {
    pl.push_back(i);
    for (int j = i; j < n + 10; j += i) vs[j] = 1;
  }
  LL ret = 0;
  for (size_t i = 0; i < pl.size(); ++i) if (pl[i] <= n && pl[i] >= 5) {
    int p1 = pl[i], p2 = pl[i + 1];
    int a = 1, b = p2 - p1, n = p2;
    while (a < p1) a *= 10;
    LL x, y, g;
    exgcd(a, n, g, x, y);
    x = x * b % n;
    if (x < 0) x += n;
    ret += a * x + p1;
    if (p1 == 19) cout << a * x + p1 << endl;;
  }
  return ret;
}

int main() {
  cout << run(1000000) << endl;
}
