#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 100000000;
int pl[MAXN], m;
void sieve() {
  for (int i = 2; i < MAXN; ++ i) {
    if (!pl[i]) pl[m ++] = i;
    for (int j = 0; j < m && pl[j] <= MAXN / i; ++ j) {
      pl[i * pl[j]] = 1;
      if (i % pl[j] == 0) break;
    }
  }
}
LL pw(LL a, LL n, LL P) {
  LL r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % P;
    a = a * a % P;
  }
  return r;
}

int solve(int st, int N, int P) {
  LL ret = 1;
  while (st < m && N / pl[st]) {
    int cur = N / pl[st];
    int left = st, right = m - 1;
    while (left < right) {
      int mid = (left + right + 1) >> 1;
      if (N / pl[mid] == cur) left = mid;
      else right = mid - 1;
    }
    ret = ret * pw(cur + 1, left - st + 1, P) % P; st = left + 1;
  }
  return ret;
}

int main() {
  sieve();
  int T; scanf("%d", &T);
  for (int _ = 0; _ < T; ++ _) {
    int N, P, st; scanf("%d%d", &N, &P);
    LL ret = 1;
    for (st = 1; pl[st] * pl[st] <= N; ++ st) {
      int cnt = 0;
      for (LL x = pl[st]; N >= x; x *= pl[st]) cnt += N / x;
      ret = ret * (cnt + 1) % P;
    }
    ret = ret * solve(st, N, P) % P;
    ret = (ret + P - 1) % P;
    printf("%d\n", (int)ret);
  }
  return 0;
}
