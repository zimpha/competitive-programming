#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 30;

int64 a[N], b[N], S;
int n;

int main() {
  scanf("%d%lld", &n, &S);
  for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
  int x = n / 2, y = n - x;
  for (int i = 0; i < y; ++i) b[i] = a[i + x];
  std::vector<std::pair<int64, int>> all(1 << ((x - 1) * 2));
  for (int mask = 0; mask < (1 << ((x - 1) * 2)); ++mask) {
    int64 sum = a[0];
    for (int i = 0; i < x - 1; ++i) {
      int o = (mask >> (i * 2)) & 3;
      if (o == 0) sum += a[i + 1];
      else if (o == 1) sum -= a[i + 1];
      else if (o == 2) sum += a[i + 1] * 2;
      else if (o == 3) sum -= a[i + 1] * 2;
    }
    all[mask] = {sum, mask};
  }
  std::sort(all.begin(), all.end());
  bool find = false;
  for (int mask = 0; mask < (1 << (y * 2)); ++mask) {
    int64 sum = 0;
    for (int i = 0; i < y; ++i) {
      int o = (mask >> (i * 2)) & 3;
      if (o == 0) sum += b[i];
      else if (o == 1) sum -= b[i];
      else if (o == 2) sum += b[i] * 2;
      else if (o == 3) sum -= b[i] * 2;
    }
    auto it = std::lower_bound(all.begin(), all.end(), std::make_pair(S - sum, -1));
    if (it != all.end() && it->first == S - sum) {
      for (int i = 0; i < x - 1; ++i) {
        int o = it->second >> (i * 2) & 3;
        putchar("+-.~"[o]);
      }
      for (int i = 0; i < y; ++i) {
        putchar("+-.~"[mask >> (i * 2) & 3]);
      }
      puts("");
      find = true;
    }
    if (find) break;
  }
  if (!find) puts("Impossible");
  return 0;
}
