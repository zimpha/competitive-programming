#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::pair<int, int>> iv(n);
    std::vector<int> idx(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &iv[i].first, &iv[i].second);
      idx[i] = i;
    }
    std::sort(idx.begin(), idx.end(), [&](int x, int y) {
      return iv[x] < iv[y];
    });
    int ends[2] = {0, 0};
    std::string ret(n, 'C');
    for (int i = 0; i < n; ++i) {
      bool found = false;
      for (int j = 0; j < 2; ++j) {
        if (iv[idx[i]].first >= ends[j]) {
          ends[j] = iv[idx[i]].second;
          found = true;
          ret[idx[i]] = "CJ"[j];
          break;
        }
      }
      if (!found) ret = "IMPOSSIBLE";
      if (!found) break;
    }
    printf("Case #%d: %s\n", cas, ret.c_str());
  }
  return 0;
}
