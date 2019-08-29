#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

int sgn(const std::vector<int> &w, int x) {
  if (x == 0) return w.back() >= 0;
  int64 r = 0;
  for (auto &e: w) r = r * x + e;
  if (x == 1 || x == -1) return r >= 0;
  r = 0;
  int cnt = 0;
  for (auto &e: w) {
    r = r * x + e;
    ++cnt;
    if (std::abs(r) > 10000000000000ll) break;
  }
  if (x < 0 && (w.size() - 1 - cnt) % 2 == 0) r = -r;
  return r >= 0;
}

int main() {
  int s, x, r = 0;
  scanf("%d%d", &s, &x);
  std::vector<int> w(s);
  for (int i = 0; i < s; ++i) {
    scanf("%d", &w[i]);
    r = r * x + w[i];
    r %= 1000;
  }
  if (r < 0) r += 1000;
  if (!sgn(w, x)) r = 1000 - r;
  printf("%03d\n", r);
  return 0;
}
