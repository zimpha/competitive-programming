#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<double> p(n);
  for (int i = 0; i < n; ++i) {
    int a, b;
    scanf("%d/%d", &a, &b);
    p[i] = 1.0 * a / b;
  }
  std::sort(p.begin(), p.end());
  puts(p[0] + p[1] > p.back() ? "TAK" : "NIE");
  return 0;
}
