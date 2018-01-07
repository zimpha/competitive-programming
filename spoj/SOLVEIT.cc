#include <cstdio>
#include <set>

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::set<int> s;
  for (int i = 0; i < q; ++i) {
    int op, x;
    scanf("%d%d", &op, &x);
    if (op == 1) {
      s.insert(x);
    } else {
      auto it = s.lower_bound(x);
      if (it == s.end()) puts("-1");
      else printf("%d\n", *it);
    }
  }
  return 0;
}
