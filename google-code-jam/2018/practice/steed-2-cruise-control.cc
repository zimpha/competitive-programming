#include <cstdio>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int D, n;
    scanf("%d%d", &D, &n);
    double need = 0;
    for (int i = 0; i < n; ++i) {
      int K, S;
      scanf("%d%d", &K, &S);
      need = std::max(need, double(D - K) / S);
    }
    printf("Case #%d: %.10f\n", cas, D / need);
  }
  return 0;
}
