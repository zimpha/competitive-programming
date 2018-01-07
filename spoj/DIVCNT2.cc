#include <cstdio>
#include <vector>

int sum(int n) {
  std::vector<int> mu(n + 1), sigma(n + 1);
  for (int i = 1; i <= n; ++i) {
    mu[i] += i == 1;
    sigma[i] += 1;
    for (int j = i + i; j <= n; j += i) mu[j] -= mu[i], sigma[j]++;
  }
  int ret = 0;
  for (int d = 1; d <= n; ++d) {
    for (int i = 1; i <= n / d; ++i) {
      ret += mu[i] * sigma[d] * sigma[d];
    }
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    printf("%d\n", sum(n));
  }
  return 0;
}
