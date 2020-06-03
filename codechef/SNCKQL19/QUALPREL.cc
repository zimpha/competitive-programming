#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k;
    scanf("%d%d", &n, &k);
    std::vector<int> s(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &s[i]);
    }
    std::sort(s.begin(), s.end());
    std::reverse(s.begin(), s.end());
    int ret = k;
    while (ret <= n && s[ret - 1] == s[k - 1]) ++ret;
    printf("%d\n", ret - 1);
  }
  return 0;
}
