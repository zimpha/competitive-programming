#include <cstdio>
#include <vector>

int main() {
  int n, m, w;
  scanf("%d%d%d", &n, &m, &w);
  std::vector<int> s(w + 1);
  for (int i = 0, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    s[x] += 1; s[y + 1] -= 1;
  }
  for (int i = 1; i <= w; ++i) s[i] += s[i - 1];
  for (int i = 0, x; i < m; ++i) {
    scanf("%d", &x);
    printf("%d\n", s[x]);
  }
  return 0;
}
