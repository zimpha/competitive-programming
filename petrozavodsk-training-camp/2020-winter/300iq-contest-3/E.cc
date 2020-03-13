#include <cstdio>
#include <vector>

const int N = 1 << 21;

int cnt[N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    cnt[x] ^= 1;
  }
  for (int i = n; i >= 0; --i) cnt[i] ^= cnt[i + 1];
  std::vector<int> ret(n + 1);
  for (int b = 0; b < 20; ++b) {
    int m = 1 << (b + 1);
    std::vector<bool> s(n + 1, 0);
    for (int i = n; i >= 0; --i) {
      s[i] = (i + m <= n) ? s[i + m] : 0;
      s[i] = s[i] ^ (cnt[i + m / 2] ^ cnt[i + m]);
    }
    for (int x = 2; x <= n + 1; ++x) {
      int u = x / m * m;
      for (int k = 0; k <= n; k += x) {
        ret[x - 1] ^= (s[k] ^ (k + u <= n ? s[k + u] : 0)) << b;
        if (k + u + m / 2 < k + x) {
          ret[x - 1] ^= (cnt[k + u + m / 2] ^ cnt[k + x]) << b;
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (ret[i]) printf("Alice");
    else printf("Bob");
    if (i == n) puts("");
    else putchar(' ');
  }
  return 0;
}
