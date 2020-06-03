#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>

const int N = 1e6 + 10;
using int64 = long long;

char s[N], t[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d%s", &n, s);
    int l = 0;
    while (l < n && s[l] == '#') ++l;
    for (int i = l; i < n; ++i) s[i - l] = s[i];
    n -= l;
    if (n == 0) {
      puts("0");
      continue;
    }
    std::vector<int> cnt;
    for (int i = 0, j; i < n; i = j) {
      for (j = i; j < n && s[i] == s[j]; ++j);
      cnt.push_back(j - i);
    }
    if (cnt.size() % 2 == 0) {
      puts("-1");
      continue;
    }
    int m = 0, need = 0;
    for (int i = 0; i < cnt[0]; ++i) t[m++] = '.';
    for (int i = 1; i < cnt.size(); i += 2) {
      int a = cnt[i], b = cnt[i + 1];
      for (int j = 0; j < a; ++j) t[m++] = '#', t[m++] = '.';
      int extra = std::min(need, b);
      b -= extra;
      need -= extra;
      for (int j = 0; j < b - a; ++j) t[m++] = '.';
      if (a > b) need += a - b;
    }
    if (m > n) {
      puts("-1");
      continue;
    }
    std::vector<int> a, b;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '#') a.push_back(i);
      if (t[i] == '#') b.push_back(i);
    }
    int64 ret = 0;
    for (size_t i = 0; i < a.size(); ++i) {
      ret += b[i] - a[i];
      ret += b[i] - i;
    }
    printf("%lld\n", ret);
  }
  return 0;
}
