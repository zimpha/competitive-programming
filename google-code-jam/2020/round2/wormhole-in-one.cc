#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
  }
  return 0;
}
