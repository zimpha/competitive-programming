#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
unsigned int pw[100];

unsigned solve(LL n) {
  unsigned int ret = 0;
  for (LL l = 2, i = 0; ; l <<= 1, ++ i) {
    if (n < l / 2) break;
    LL cnt = (n + 1) / l * l / 2;
    if ((n + 1) % l) cnt += max(0ll, (n + 1) % l - (l / 2));
    cnt %= 1ll << 32;
    ret += (unsigned int)cnt * pw[i];
  }
  return ret;
}

unsigned brute(int l, int r) {
  unsigned ret = 0;
  for (int n = l; n <= r; ++ n) {
    for (int i = 0; i < 32; ++ i) {
      if (n >> i & 1) ret += pw[i];
    }
  }
  return ret;
}

int main() {
  pw[0] = 1;
  for (int i = 1; i < 100; ++ i) pw[i] = pw[i - 1] * 3u;
  int T; scanf("%d", &T);
  for (int _ = 0; _ < T; ++ _) {
    LL L, R; scanf("%lld%lld", &L, &R);
    printf("%u\n", solve(R) - solve(L - 1));
  }
  return 0;
}
