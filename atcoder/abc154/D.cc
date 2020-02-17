#include <cstdio>
#include <vector>

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  std::vector<double> sum(n + 1);
  double ret = 0;
  for (int i = 1; i <= n; ++i) {
    int p;
    scanf("%d", &p);
    sum[i] = (p + 1) * 0.5 + sum[i - 1];
    if (i >= k && sum[i] - sum[i - k] >= ret) ret = sum[i] - sum[i - k];
  }
  printf("%.10f\n", ret);
  return 0;
}
