#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

__int128 gcd(__int128 a, __int128 b) {
  if (b == 0) return a;
  else return gcd(b, a % b);
}

struct frac {
  __int128 x, y;
  void fix() {
    __int128 g = gcd(x, y);
    x /= g; y /= g;
  }
  frac(): x(0), y(1) {}
  frac(__int128 a, __int128 b): x(a), y(b) {fix();}
  frac operator + (const frac &r) const {
    return frac(x * r.y + y * r.x, y * r.y);
  }
  frac operator * (const frac &r) const {
    return frac(x * r.x, y * r.y);
  }
  frac operator / (const frac &r) const {
    return frac(x * r.y, y * r.x);
  }
  bool operator == (const frac &r) const {
    return x == r.x && y == r.y;
  }
  bool operator < (const frac &r) const {
    return x * r.y < y * r.x;
  }
  bool sqrt() {
    LL s = ::sqrt((LL)x), t = ::sqrt((LL)y);
    if (x != s * s || y != t * t) return 0;
    x = s; y = t; fix(); return 1;
  }
};


LL run(int n) {
  vector<frac> ab;
  for (int b = 1; b <= n; ++b) {
    for (int a = 1; a < b; ++a) {
      if (__gcd(a, b) != 1) continue;
      ab.push_back(frac(a, b));
    }
  }
  set<frac> sol;
  for (size_t i = 0; i < ab.size(); ++i) {
    frac &x = ab[i];
    for (size_t j = i; j < ab.size(); ++j) {
      frac &y = ab[j], z;
      z = x + y;
      if (z.x < z.y && z.y <= n) sol.insert(x + y + z);
      z = x * x + y * y;
      if (z.x < z.y && z.y <= n * n && z.sqrt()) sol.insert(x + y + z);
      z = x * y / (x + y);
      if (z.x < z.y && z.y <= n) sol.insert(x + y + z);
      z = x * x * y * y / (x * x + y * y);
      if (z.x < z.y && z.y <= n * n && z.sqrt()) sol.insert(x + y + z);
    }
  }
  frac r;
  cout << sol.size() << endl;
  for (auto e: sol) r = r + e;
  __int128 s = r.x + r.y;
  const LL md = 100000000000000000ll;
  printf("%lld%017lld\n", LL(s / md), LL(s % md));
}

int main() {
  run(35);
  return 0;
}
