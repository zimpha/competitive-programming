#include <cstdio>
#include <functional>
#include <algorithm>
#include <vector>

bool valid(std::vector<int> a) {
  std::vector<int> dsu(a.size());
  for (size_t i = 0; i < a.size(); ++i) dsu[i] = i;
  std::function<int(int)> root = [&](int x) -> int {
    if (x != dsu[x]) dsu[x] = root(dsu[x]);
    return dsu[x];
  };
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (std::__gcd(a[i], a[j]) == 1) {
        dsu[root(i)] = root(j);
      }
    }
  }
  for (size_t i = 0; i < a.size(); ++i) {
    if (root(i) != root(0)) return false;
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      cnt += a[i] == 47;
    }
    int ret = 0;
    if (valid(a)) ret = 0;
    else if (cnt == a.size()) {
      ret = 1;
      a[0] = 2;
    } else if (cnt == 0) {
      ret = 1;
      a[0] = 47;
    }
    printf("%d\n", ret);
    for (auto &&x : a) printf("%d ", x);
    puts("");
  }
  return 0;
}
