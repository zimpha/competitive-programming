#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

using ll = long long;

bool check(ll a, ll b, ll c) {
  return a + b > c;
}

ll best[200][200];

int main() {
  int n;
  scanf("%d", &n);
  std::vector<ll> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
  }
  std::sort(a.begin(), a.end(), std::greater<ll>());
  int m = std::min(n, 150);
  std::reverse(a.begin(), a.begin() + m);
  ll ret = 0;
  memset(best, 0, sizeof(best));
  for (int i = 0; i < m; ++i) {
    for (int j = i + 2; j < m; ++j) {
      if (check(a[j - 2], a[j - 1], a[j])) {
        best[i][j] = std::max(best[i][j - 1], a[j - 2] + a[j - 1] + a[j]);
      } else {
        best[i][j] = best[i][j - 1];
      }
    }
  }
  static ll buffer[200];
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      int cnt = 0;
      if (i >= 2) buffer[cnt++] = a[i - 2];
      if (i >= 1) buffer[cnt++] = a[i - 1];
      if (j - i <= 5) {
        for (int k = i + 1; k < j; ++k) buffer[cnt++] = a[k];
      } else {
        buffer[cnt++] = a[i + 1];
        buffer[cnt++] = a[i + 2];
        buffer[cnt++] = a[j - 2];
        buffer[cnt++] = a[j - 1];
      }
      for (int k = j + 1; k < m; ++k) {
        if (a[i] + a[j] <= a[k]) break;
        int t_cnt = cnt;;
        if (k - j <= 5) {
          for (int l = j + 1; l < k; ++l) buffer[t_cnt++] = a[l];
        } else {
          buffer[t_cnt++] = a[j + 1];
          buffer[t_cnt++] = a[j + 2];
          buffer[t_cnt++] = a[k - 2];
          buffer[t_cnt++] = a[k - 1];
        }
        if (k + 1 < m) buffer[t_cnt++] = a[k + 1];
        if (k + 2 < m) buffer[t_cnt++] = a[k + 2];
        ll mx = i ? best[0][i - 1] : 0;
        mx = std::max(mx, std::max(best[i + 1][j - 1], best[j + 1][k - 1]));
        mx = std::max(mx, best[k + 1][m - 1]);
        for (int l = 0; l + 2 < t_cnt; ++l) {
          if (check(buffer[l], buffer[l + 1], buffer[l + 2])) {
            mx = std::max(mx, buffer[l] + buffer[l + 1] + buffer[l + 2]);
          }
        }
        if (mx) {
          ret = std::max(ret, mx + a[i] + a[j] + a[k]);
        }
      }
    }
  }
  std::cout << ret << std::endl;
  return 0;
}
