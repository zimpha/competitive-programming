#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::pair<int, int>> w1(n), w2(n);
    for (int i = 0; i < n; ++i) {
      int l, a, b;
      scanf("%d%d%d", &l, &a, &b);
      w1[i] = {a, l};
      w2[i] = {b, l};
    }
    std::sort(w1.begin(), w1.end());
    std::sort(w2.begin(), w2.end());
    std::reverse(w1.begin(), w1.end());
    std::reverse(w2.begin(), w2.end());
    int64 balance = 0;
    bool valid = true;
    for (int i = 0, j = 0; valid; ) {
      if (w1[i].second == 0) ++i;
      if (w2[j].second == 0) ++j;
      if (i == n && j == n) break;
      assert(i < n && j < n);
      int x = std::min(w1[i].second, w2[j].second);
      w1[i].second -= x; w2[j].second -= x;
      balance += int64(w1[i].first - w2[j].first) * x;
      if (balance < 0) valid = false;
    }
    valid &= balance == 0;
    puts(valid ? "TAK" : "NIE");
  }
  return 0;
}
