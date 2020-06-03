#include <cstdio>
#include <vector>
#include <set>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::set<std::vector<bool>> s;
  for (int i = 0; i < n; ++i) {
    std::vector<bool> t(500);
    for (int j = i; j < n; ++j) {
      t[a[j] - 1] = 1;
      s.insert(t);
    }
  }
  printf("%d\n", (int)s.size());
  return 0;
}
