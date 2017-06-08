#include <cstdio>
#include <string>

using ll = long long;

ll cnt[10], sum[10];

int main() {
  cnt[0] = 1;
  for (int i = 1; i < 10; ++i) {
    cnt[i] = cnt[i - 1] * 26;
  }
  for (int i = 0; i < 10; ++i) {
    sum[i] = cnt[i];
    if (i) sum[i] += sum[i - 1];
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m = 0;
    scanf("%d", &n);
    ++n;
    while (sum[m] < n) ++m;
    n -= sum[m - 1];
    std::string s(10, 0);
    for (int d = 0; d < m; ++d) {
      int now = 0;
      for (int i = 0; i < 26; ++i) {
        now += cnt[m - d - 1];
        if (now >= n) {
          s[d] = 'A' + i;
          n -= cnt[m - d - 1] * i;
          break;
        }
      }
    }
    puts(s.c_str());
  }
  return 0;
}
