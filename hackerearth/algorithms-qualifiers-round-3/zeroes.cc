#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 10;
int pl[MAXN], cnt[MAXN], m;
int mp[MAXN], A[MAXN], n, Q;

int main() {
  for (int i = 2; i < MAXN; ++ i) {
    if (!mp[i]) mp[i] = i, pl[m ++] = i;
    for (int j = 0; j < m && pl[j] * i < MAXN; ++ j) {
      mp[i * pl[j]] = pl[j];
      if (i % pl[j] == 0) break;
    }
  }
  scanf("%d", &n);
  for (int i = 0; i < n; ++ i) {
    int x; scanf("%d", &x);
    for (; x > 1; x /= mp[x]) {
      cnt[mp[x]] ++;
    }
  }
  scanf("%d", &Q);
  for (int i = 0; i < Q; ++ i) {
    int x; scanf("%d", &x);
    int ret = 1e9, p(0), s(0);
    for (; x > 1; x /= mp[x]) {
      if (p == mp[x]) ++ s;
      else {
        if (s) ret = min(ret, cnt[p] / s);
        p = mp[x]; s = 1;
      }
    }
    ret = min(ret, cnt[p] / s);
    printf("%d\n", ret);
  }
  return 0;
}
