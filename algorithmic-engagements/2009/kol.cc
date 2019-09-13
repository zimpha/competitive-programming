#include <cstdio>
#include <vector>
#include <functional>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> sum(n), a(n * 2);
  std::vector<int> deg(n * 2);
  std::vector<int> dsu(n * 2);
  for (int i = 0; i < n * 2; ++i) {
    scanf("%d", &a[i]);
    sum[--a[i]] += i;
    dsu[i] = i;
  }

  std::function<int(int)> root = [&](int x) {
    if (x != dsu[x]) dsu[x] = root(dsu[x]);
    return dsu[x];
  };
  
  int ret = n * 2;
  for (int i = 0; i < n * 2; ++i) {
    int x = i % n, y = x + n;
    x = root(x), y = root(y);
    if (x != y) dsu[x] = y, --ret;
    x = root(i), y = root(sum[a[i]] - i);
    if (x != y) dsu[x] = y, --ret;
  }
  printf("%lld\n", 1ll << ret);
  return 0;
}
