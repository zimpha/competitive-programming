#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a((1 << n) - 1);
    for (int i = 0; i < (1 << n) - 1; ++i) {
      scanf("%d", &a[i]);
    }
    std::sort(a.begin(), a.end());
    std::vector<int> ret(n);
    bool valid = true;
    for (int i = 0; i < n && valid; ++i) {
      std::vector<bool> mark(a.size());
      std::vector<int> buffer;
      ret[i] = a[0];
      for (size_t x = 1, y = 1; x < a.size(); ++x) {
        while (x < a.size() && mark[x]) ++x;
        if (x == a.size()) break;
        if (y <= x) y = x + 1;
        mark[x] = true;
        buffer.push_back(a[x]);
        for (; y < a.size() && (mark[y] || a[y] < a[x] + a[0]); ++y);
        if (y == a.size() || a[y] != a[x] + a[0]) valid = false;
        if (!valid) break;
        mark[y] = true;
      }
      a.swap(buffer);
    }
    if (!valid) puts("NO");
    else {
      for (auto &x: ret) printf("%d ", x);
      puts("");
    }
  }
  return 0;
}
