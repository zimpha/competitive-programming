#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

int main() {
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    printf("Case %d:\n", cas);
    int n, k;
    std::cin >> n >> k;
    std::map<std::string, int> cnt;
    std::set<std::pair<int, std::string>> ss;
    std::vector<std::string> s(n);
    auto del = [&](int x) {
      auto it = cnt.find(s[x]);
      ss.erase({-it->second, it->first});
      it->second--;
      if (it->second != 0) {
        ss.emplace(-it->second, it->first);
      }
    };
    auto add = [&](int x) {
      cnt[s[x]]++;
      ss.emplace(-cnt[s[x]], s[x]);
    };
    for (int i = 0; i < n; ++i) {
      if (i >= k) del(i - k);
      std::cin >> s[i];
      add(i);
      std::cout << ss.begin()->second << ' ' << -ss.begin()->first << '\n';
    }
  }
  return 0;
}
