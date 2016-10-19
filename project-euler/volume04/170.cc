#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

bool gao(LL n, int &s) {
  while (n) {
    int o = n % 10;
    if (s >> o & 1) return s ^= 1 << o, false;
    s |= 1 << o;
    n /= 10;
  }
  return true;
}

bool check(vector<LL> &v) {
  LL g = 0;
  for (auto &e: v) g = __gcd(g, e);
  if (g == 1) return 0;
  for (int m = 3; m < 49; m += 3) if (g % m == 0) {
    int s = 0;
    if (!gao(m, s)) continue;
    for (auto &e: v) if (!gao(e / m, s)) break;
    if (s == 1023) return true;
  }
  return false;
}

int main() {
  int p[10] = {9, 8, 0, 1, 2, 3, 4, 5, 6, 7};
  do {
    for (int msk = 1; msk < 512; ++msk) {
      vector<LL> v; LL r = 9;
      for (int i = 0; i < 9; ++i) {
        if (msk >> i & 1) v.push_back(r), r = p[i + 1];
        else r = r * 10 + p[i + 1];
      }
      v.push_back(r);
      if (check(v)) {
        for (auto &e: v) printf("%lld ", e); printf(": ");
        for (int i = 0; i < 10; ++i) printf("%d", p[i]); puts("");
        break;
      }
    }
  } while (next_permutation(p + 2, p + 10));
  return 0;
}
