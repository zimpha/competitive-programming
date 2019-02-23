#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  int sum[2] = {0, 0};
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum[i & 1] += a[i];
  }
  int cnt = 0;
  int sum2[2] = {0, 0};
  for (int i = 0; i < n; ++i) {
    sum[i & 1] -= a[i];
    if (sum2[0] + sum[1] - sum2[1] == sum2[1] + sum[0] - sum2[0]) ++cnt;
    sum[i & 1] += a[i];
    sum2[i & 1] += a[i];
  }
  printf("%d\n", cnt);
  return 0;
}
