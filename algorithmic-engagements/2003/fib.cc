#include <cstdio>
#include <vector>

int main() {
  std::vector<long long> f = {0, 1};
  int n;
  scanf("%d", &n);
  for (int i = 2; i <= n; ++i) {
    f.push_back(f[i - 1] + f[i - 2]);
  }
  printf("%lld\n", f[n]);
  return 0;
}
