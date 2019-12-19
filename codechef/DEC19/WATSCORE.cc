#include <cstdio>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> score(11);
    for (int i = 0; i < n; ++i) {
      int p, x;
      scanf("%d%d", &p, &x);
      if (p <= 8 && score[p - 1] < x) score[p - 1] = x;
    }
    int sum = 0;
    for (int i = 0; i < 11; ++i) sum += score[i];
    printf("%d\n", sum);
  }
  return 0;
}
