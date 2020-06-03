#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::vector<int>> ret;
  if (n == 2) puts("-1");
  else if (n == 3) puts("3\n1 3 2\n2 3 1\n3 1 2");
  else if (n == 4) puts("3\n4 3 1 2\n1 4 2 3\n2 4 1 3");
  else if (n % 2 == 1) {
    for (int l = 1; l < n; l <<= 1) {
      std::vector<int> a(n);
      for (int i = 0; i < n; ++i) a[i] = (i + l) % n + 1;
      ret.push_back(a);
    }
  } else {
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = i + 1;
    a[n - 3] = n - 1; a[n - 2] = n; a[n - 1] = n - 2;
    ret.push_back(a);
    for (int i = 0; i < n; ++i) a[i] = i + 1;
    for (int i = 0; i < n / 4; ++i) {
      a[i * 4 + 0] = i * 4 + 2;
      a[i * 4 + 1] = i * 4 + 4;
      a[i * 4 + 2] = i * 4 + 1;
      a[i * 4 + 3] = i * 4 + 3;
    }
    ret.push_back(a);
    for (int l = 1; l * 2 < n; l <<= 1) {
      for (int i = 0; i < n; ++i) a[i] = (i + l) % n + 1;
      ret.push_back(a);
    }
  }
  if (n > 4 || n == 1) {
    printf("%d\n", (int)ret.size());
    for (auto &a: ret) {
      for (auto &x: a) printf("%d ", x);
      puts("");
    }
  }
  return 0;
}
