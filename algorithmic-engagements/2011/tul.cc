#include <cstdio>
#include <set>

int main() {
  int n;
  scanf("%d", &n);
  std::set<int> s;
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    s.insert(x);
  }
  printf("%d\n", 15000 - (int)s.size());
  return 0;
}
