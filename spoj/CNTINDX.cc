#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

int main() {
  int Q;
  scanf("%d", &Q);
  std::map<int, std::vector<int>> pos;
  std::vector<int> a;
  while (Q--) {
    int op, x;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d", &x);
      a.push_back(x);
      pos[x].push_back(a.size());
    } else if (op == 0) {
      if (a.empty()) puts("invalid");
      else {
        pos[a.back()].pop_back();
        a.pop_back();
      }
    } else {
      int l, r;
      scanf("%d%d%d", &x, &l, &r);
      if (pos.count(x)) {
        auto &v = pos[x];
        printf("%lu\n", std::upper_bound(v.begin(), v.end(), r) - std::lower_bound(v.begin(), v.end(), l));
      } else {
        puts("0");
      }
    }
  }
  return 0;
}
