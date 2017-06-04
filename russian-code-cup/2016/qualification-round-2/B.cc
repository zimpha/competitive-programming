#include <cstdio>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; ++i) {
      scanf("%d", &b[i]);
    }
    char s[n + m + 10];
    scanf("%s", s);
    std::sort(a.begin(), a.end());
    std::multiset<int> send(b.begin(), b.end());
    int total = 0, ret = 0;
    for (int i = 0; i < n + m; ++i) {
      if (s[i] == '+') {
        total += a.back();
        a.pop_back();
      } else {
        if (total < *send.begin()) {
          send.erase(send.find(*send.rbegin()));
          ++ret;
        } else {
          total -= *send.begin();
          send.erase(send.begin());
        }
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}
