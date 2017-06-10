#include <cstdio>

const int N = 10000000 + 10;

int mp[N], p[N], m;

void sieve() {
  for (int i = 2; i < N; ++i) {
    if (!mp[i]) mp[i] = i, p[m++] = i;
    for (int j = 0; j < m && p[j] * i < N; ++j) {
      mp[p[j] * i] = p[j];
      if (i % p[j] == 0) break;
    }
  }
}

int main() {
  sieve();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int a, b, n, ret = 0;
    scanf("%d%d%d", &a, &b, &n);
    for (int i = a; i <= b; ++i) {
      int last = -1, cnt = 0;
      for (int m = i; m != 1; m /= mp[m]) {
        if (last != mp[m]) last = mp[m], ++cnt;
      }
      ret += cnt == n;
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}
