#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e5 + 10;

char s[N];

std::vector<int> manacher(char *s, int n) {
  std::vector<int> u(n <<= 1, 0);
  for (int i = 0, j = 0, k; i < n; i += k, j = std::max(j - k, 0)) {
    while (i >= j && i + j + 1 < n && s[(i - j) >> 1] == s[(i + j + 1) >> 1]) ++j;
    for (u[i] = j, k = 1; i >= k && u[i] >= k && u[i - k] != u[i] - k; ++k) {
      u[i + k] = std::min(u[i - k], u[i] - k);
    }
  }
  return u;
}

int solve(int n) {
  if (n == 1) return -1;
  auto d = manacher(s, n);
  if (d[n - 1] != n) return 1;
  for (int i = 0; i + 1 < n; ++i) {
    if (d[i] != i + 1 && d[i + n] != n - i - 1) return 2;
  }
  return -1;
}

int main() {
  int n;
  scanf("%d%s", &n, s);
  printf("%d\n", solve(n));
  return 0;
}
