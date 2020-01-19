#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::sort(a.begin(), a.end());
  std::vector<bool> suffix(n + 1);
  suffix[n] = suffix[n - 1] = suffix[n - 2] = 1;
  for (int i = n - 3; i >= 0; --i) {
    if (a[i] - a[i + 1] == a[i + 1] - a[i + 2]) suffix[i] = 1;
    else break;
  }
  for (int x = 0; x < 4 && n; ++x) {
    for (int y = x + 1; y < 4 && n; ++y) {
      std::vector<int> A, B, mark(n);
      int u = a[x], da = a[y] - a[x], db = -1;
      bool valid = false;
      for (int i = 0; i < n && !valid; ++i) {
        if (a[i] > u) break;
        if (a[i] == u) A.push_back(a[i]), u += da, mark[i] = 1;
        else B.push_back(a[i]), mark[i] = 1;
        if (B.size() >= 2) db = B[1] - B[0];
        if (B.size() >= 3) {
          if (B[B.size() - 1] - B[B.size() - 2] != db) break;
        }
        if (B.empty() && suffix[i + 1]) valid = true;
        if (suffix[i + 1] && !valid) {
          int ds = i + 2 < n ? a[i + 2] - a[i + 1] : -1;
          int dt = i + 1 < n ? a[i + 1] - B.back() : -1;
          if (dt == -1) valid = true;
          if (ds != -1 && ds != dt) continue;
          if (db != -1 && db != dt) continue;
          valid = true;
        }
      }
      if (!valid) continue;
      for (int i = 0; i < n; ++i) {
        if (!mark[i]) B.push_back(a[i]);
      }
      if (B.empty()) B.push_back(A.back()), A.pop_back();
      printf("%d\n", (int)A.size());
      for (auto &x: A) printf("%d ", x);
      puts("");
      printf("%d\n", (int)B.size());
      for (auto &x: B) printf("%d ", x);
      puts("");
      return 0;
    }
  }
  puts("-1");
  return 0;
}
