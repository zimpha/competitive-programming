#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n, ut;
  scanf("%d%d", &n, &ut);
  std::vector<int> l(n), v(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &l[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
  }
  for (int i = 0; i < n; ++i) {
    int ret = 0;
    for (int j = 0; j < n; ++j) {
      if ((v[i] < 0 && v[j] > 0) || (v[i] > 0 && v[j] < 0)) {
        int dab = v[i] > 0 ? l[j] - l[i] : l[i] - l[j];
        int vab = std::abs(v[i] - v[j]);
        if (dab < 0) dab += 1000;
        if (dab <= vab * ut) {
          ret += (ut * vab - dab) / 1000 + 1;
        }
      }
    }
    if (i) putchar(' ');
    printf("%d", ret);
  }
  puts("");
  return 0;
}
