#include <cstdio>
#include <cassert>
#include <algorithm>

using ll = long long;

const int N = 100000 + 10;
int s[N], t[N], u[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    s[0] = t[0] = 1e9 + 1;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", s + i);
    }
    for (int i = 1; i <= n; ++i) {
      scanf("%d", t + i);
    }
    s[n + 1] = t[n + 1] = 1;
    n += 2;
    int m = 0;
    bool flag = false;
    for (int i = 0; i < n; ++i) {
      if (s[i] == 0 && t[i] != 0) {
        flag = true;
        break;
      }
      if (s[i] == 0 && t[i] == 0) continue;
      s[m] = s[i];
      t[m] = t[i];
      u[m++] = s[i] - t[i];
    }
    if (flag) {
      puts("-1");
      continue;
    }
    ll base = 0, a = 0, b = 0, Q = 0;
    for (int i = 1, j = 0; i < m; ++i) {
      if (t[i] == 0) {
        Q = std::max<ll>(Q, s[i]);
      } else {
        ll R = u[j] - u[i];
        ll d_min = std::max<ll>(u[i], 0);
        ll d_max = std::max<ll>(s[i] - 1, 0);
        base += std::max<ll>(Q - a, 0);
        if (R >= 0) {
          assert(a <= b);
          if (Q <= a) {
            a = a - R;
          } else if (Q <= b) {
            a = Q - R;
          } else {
            a = b - R;
            b = Q;
          }
        } else {
          if (Q <= a) {
            b = b - R;
          } else if (Q <= b) {
            a = Q;
            b = b - R;
          } else {
            a = std::min(Q, b - R);
            b = std::max(Q, b - R);
          }
        }
        if (d_min <= a) base += 0;
        else if (d_min <= b) base += d_min - a;
        else base += d_min - a - b;
        a = std::max<ll>(d_min, std::min<ll>(a, d_max));
        b = std::max<ll>(a, std::min<ll>(b, d_max));
        j = i;
        Q = 0;
      }
    }
    printf("%lld\n", base);
  }
  return 0;
}
