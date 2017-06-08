#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>

using ll = long long;
const int N = 2000 + 10;

struct point {
  ll x, y;
  bool operator < (const point &r) const {
    if (y <= 0 && r.y > 0) return true;
    if (y > 0 && r.y <= 0) return false;
    if (y == 0 && r.y == 0) return x < r.x;
    return x * r.y - y * r.x > 0;
  }
} Q[N], P[N];

bool isacute(const point &a, const point &b) {
  return a.x * b.y - a.y * b.x >= 0 && a.x * b.x + a.y * b.y > 0;
}

bool isacute2(const point &a, const point &b) {
  return a.x * b.y - a.y * b.x > 0 && a.x * b.x + a.y * b.y > 0;
}

int obtuse(int n) {
    int ans = 0;
    std::sort(Q + 1, Q + n);
    for (int i = 1, a = 1, b = 1; i < n; ++i) {
        while (isacute(Q[i], Q[a]) && a < n) ++a;
        while (!isacute2(Q[b], Q[i]) && b < n) ++b;
        ans += b - a;
    }
    return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%lld%lld", &P[i].x, &P[i].y);
    }
    ll res = 1ll * n * (n - 1) * (n - 2) / 6;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; ++j) Q[j].x = Q[j].y = 0;
        int k = 0;
        for (int j = 1; j <= n; ++j) if (j != i) {
          Q[++k].x = P[j].x - P[i].x;
          Q[k].y = P[j].y - P[i].y;
        }
        res -= obtuse(n);
    }
    printf("%lld\n", res);
  }
  return 0;
}
