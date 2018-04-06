#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m = 0;
    scanf("%d", &n);
    std::vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &cnt[i]);
      m += cnt[i];
    }
    printf("Case #%d:", cas);
    while (m) {
      std::string remove = "";
      std::vector<std::pair<int, int>> all;
      for (int i = 0; i < n; ++i) if (cnt[i]) {
        all.emplace_back(cnt[i], i);
      }
      std::sort(all.begin(), all.end());
      std::reverse(all.begin(), all.end());
      if (all.size() == 2 && all[0].first == all[1].first) {
        remove += char('A' + all[0].second);
        remove += char('A' + all[1].second);
      } else {
        remove += char(all[0].second + 'A');
      }
      for (auto &&c: remove) cnt[c - 'A']--;
      m -= remove.size();
      printf(" %s", remove.c_str());
    }
    puts("");
  }
  return 0;
}
