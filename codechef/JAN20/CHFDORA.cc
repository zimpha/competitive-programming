#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e5 + 10, M = 1e6 + 10;

using int64 = long long;

std::vector<int> a[N];
std::vector<int> row[N], col[N];

std::vector<int> manacher(std::vector<int> &s, int n) {
  std::vector<int> u(n <<= 1, 0);
  for (int i = 0, j = 0, k; i < n; i += k, j = std::max(j - k, 0)) {
    while (i >= j && i + j + 1 < n && s[(i - j) >> 1] == s[(i + j + 1) >> 1]) ++j;
    for (u[i] = j, k = 1; i >= k && u[i] >= k && u[i - k] != u[i] - k; ++k) {
      u[i + k] = std::min(u[i - k], u[i] - k);
    }
  }
  return u;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
      a[i].resize(m);
      row[i].resize(m);
      col[i].resize(m);
      for (int j = 0; j < m; ++j) {
        scanf("%d", &a[i][j]);
      }
    }
    for (int i = 0; i < n; ++i) {
      auto u = manacher(a[i], m);
      for (int j = 0; j < m; ++j) {
        col[i][j] = (u[j * 2] + 1) / 2;
      }
    }
    for (int j = 0; j < m; ++j) {
      std::vector<int> s(n);
      for (int i = 0; i < n; ++i) s[i] = a[i][j];
      auto u = manacher(s, n);
      for (int i = 0; i < n; ++i) {
        row[i][j] = (u[i * 2] + 1) / 2;
      }
    }
    int64 ret = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        ret += std::min(row[i][j], col[i][j]);
      }
    }
    printf("%lld\n", ret);
  }
  return 0;
}
