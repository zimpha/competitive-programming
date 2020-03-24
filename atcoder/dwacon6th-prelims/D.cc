#include <cstdio>
#include <vector>
#include <set>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n), deg(n);
  std::set<int> left;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    ++deg[--a[i]];
    left.insert(i);
  }

  int forbid = -1;
  
  auto check = [&](int x) {
    if (x == forbid) return false;
    int y = a[x];
    if (!left.count(y)) {
      if (left.size() == 3) {
        int u = -1, v = -1;
        for (auto &e: left) if (e != x) {
          if (u == -1) u = e;
          else v = e;
        }
        if (a[u] == v && a[v] == u) return false;
      }
      return true;
    } else {
      return deg[y] != left.size() - 1;
    }
  };

  std::vector<int> b(n, -1);
  for (int i = 0; i < n; ++i) {
    for (auto it = left.begin(); it != left.end(); ++it) {
      if (check(*it)) { b[i] = *it; break; }
    }
    if (b[i] == -1) break;
    forbid = a[b[i]];
    --deg[forbid];
    left.erase(b[i]);
  }
  if (b.back() == -1) puts("-1");
  else {
    for (auto &x: b) printf("%d ", x + 1);
    puts("");
  }
  return 0;
}
