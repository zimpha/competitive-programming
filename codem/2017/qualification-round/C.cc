#include <cstdio>
#include <vector>
#include <set>
#include <map>

int main() {
  int m;
  while (scanf("%d", &m) == 1) {
    std::set<int> unknown;
    std::map<int, int> last, cnt;
    int ret = -1;
    for (int i = 0; i < m; ++i) {
      char op[10];
      scanf("%s", op);
      if (op[0] == '?') {
        unknown.insert(i);
      } else if (op[0] == 'I') {
        int x;
        scanf("%d", &x);
        if (ret != -1) continue;
        if (++cnt[x] == 2) {
          if (!last.count(x)) last[x] = -1;
          auto it = unknown.upper_bound(last[x]);
          if (it == unknown.end()) ret = i + 1;
          else unknown.erase(it);
          cnt[x] = 1;
        }
        last[x] = i;
      } else {
        int x;
        scanf("%d", &x);
        if (ret != -1) continue;
        if (--cnt[x] == -1) {
          if (!last.count(x)) last[x] = -1;
          auto it = unknown.upper_bound(last[x]);
          if (it == unknown.end()) ret = i + 1;
          else unknown.erase(it);
          cnt[x] = 0;
        }
        last[x] = i;
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}
