#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>

void ext_kmp(char *s, int n, int* z) {
  memset(z, 0, sizeof(int) * n);
  int m = n / 3 * 2;
  for (int i = 1, x = 0, y = 0; i <= m; ++i) {
    if (i <= y) z[i] = std::min(y - i, z[i - x]);
    int w = z[i];
    while (i + w < n && s[i + w] == s[w]) ++w;
    if (y <= i + w) x = i, y = i + w;
    z[i] = w;
  }
}

const int N = 1e6 + 10;

char s[N], t[N], buf[N * 3];
int u[N * 3], v[N * 3];

int main() {
  int n;
  scanf("%d%s%s", &n, s, t);
  memcpy(buf, t, n);
  memcpy(buf + n, s, n);
  memcpy(buf + n * 2, s, n);
  ext_kmp(buf, n * 3, u);
  std::reverse(s, s + n);
  std::reverse(t, t + n);
  memcpy(buf, t, n);
  memcpy(buf + n, s, n);
  memcpy(buf + n * 2, s, n);
  ext_kmp(buf, n * 3, v);
  bool valid = true;
  std::vector<int> candidate;
  for (int i = n, j = n * 2; i < n * 2 && valid; ++i, --j) {
    if (u[i] >= n) valid = false;
    else if (u[i] + v[j] == n - 1) {
      candidate.push_back(i - n);
    }
  }
  if (!valid || candidate.empty()) puts("NIE");
  else {
    puts("TAK");
    for (auto &x: candidate) printf("%d ", x);
    puts("");
  }
  return 0;
}
