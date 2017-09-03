#include <cstdio>
#include <vector>
#include <set>

const int N = 1e5 + 10;

int main() {
  int n;
  scanf("%d", &n);
  std::set<int> unknown;
  std::vector<int> inside(N), last_i(N), last_o(N);
  for (int i = 1; i <= n; ++i) {
    char opt[10];
    int x;
    scanf("%s", opt);
    if (opt[0] != '?') scanf("%d", &x);
    if (opt[0] == 'I') {
      if (inside[x]) {
        auto it = unknown.lower_bound(last_i[x]);
        if (it != unknown.end()) {
          last_o[x] = *it;
          unknown.erase(it);
        } else {
          printf("%d\n", i);
          return 0;
        }
      }
      last_i[x] = i;
      inside[x] = true;
    } else if (opt[0] == 'O') {
      if (!inside[x]) {
        auto it = unknown.lower_bound(last_o[x]);
        if (it != unknown.end()) {
          last_i[x] = *it;
          unknown.erase(it);
        } else {
          printf("%d\n", i);
          return 0;
        }
      }
      last_o[x] = i;
      inside[x] = false;
    } else {
      unknown.insert(i);
    }
  }
  puts("-1");
  return 0;
}