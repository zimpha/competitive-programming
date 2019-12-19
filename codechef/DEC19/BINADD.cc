#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 1e5 + 10;

char s[N], t[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%s%s", s, t);
    int n = strlen(s);
    int m = strlen(t);
    std::reverse(s, s + n);
    std::reverse(t, t + m);
    std::vector<int> a(n + m + 1);
    std::vector<int> b;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '1') a[i] = 1;
    }
    for (int i = 0; i < m; ++i) {
      if (t[i] == '1') b.push_back(i);
    }
    int ret = 0;
    while (!b.empty()) {
      std::vector<int> tmp;
      for (auto &x: b) if (a[x]) tmp.push_back(x + 1);
      for (auto &x: b) a[x] ^= 1;
      ++ret;
      b.swap(tmp);
    }
    printf("%d\n", ret);
  }
  return 0;
}
