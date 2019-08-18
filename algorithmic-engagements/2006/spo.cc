#include <cstdio>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> s = {2, 1, 3, 4, 7, 1, 8, 9, 7, 6, 3, 9};
  printf("%d\n", s[n % s.size()]);
  return 0;
}
