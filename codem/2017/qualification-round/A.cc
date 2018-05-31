#include <cstdio>
#include <cstring>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  int m;
  scanf("%d", &m);
  std::vector<int> b(m);
  for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
  int ret = -1;
  for (int s = 0; s + n <= m; ++s) {
    int now = 0;
    for (int i = 0; i < n; ++i) {
      now += (a[i] - b[s + i]) * (a[i] - b[s + i]);
    }
    if (ret == -1 || ret > now) ret = now;
  }
  printf("%d\n", ret);
  return 0;
}
