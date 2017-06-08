#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> p(n), q(n, -1);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &p[i]);
      --p[i];
      if (p[i] != -1) q[p[i]] = i;
    }
    std::vector<std::vector<int>> chains;
    for (int i = 0; i < n; ++i) {
      if (p[i] != -1) continue;
      std::vector<int> chain;
      for (int j = i; j != -1; j = q[j]) {
        chain.push_back(j);
      }
      std::reverse(chain.begin(), chain.end());
      chains.push_back(chain);
    }
    if (!chains.empty()) {
      int first = chains[0][0], last = -1;
      for (auto &&chain: chains) {
        for (auto &&x: chain) {
          if (last != -1) p[last] = x;
          last = x;
        }
      }
      p[last] = first;
    }
    std::vector<bool> mark(n, false);
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      if (mark[i]) continue;
      ++ret;
      for (int j = i; !mark[j]; j = p[j]) {
        mark[j] = true;
      }
    }
    printf("%d\n", n - ret);
    for (int i = 0; i < n; ++i) {
      printf("%d ", p[i] + 1);
    }
    puts("");
  }
  return 0;
}
