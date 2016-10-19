#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int lim = 4000000 * 2 - 1;
int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
int cnt[14], ret[14];
double rval;

void dfs(int dep, int last, LL sum, double val) {
  if (sum > lim) {
    rval = val;
    memcpy(ret, cnt, sizeof(cnt));
    return;
  }
  if (dep == 14) return;
  for (int i = 1; i <= last; ++i) {
    cnt[dep] = i;
    double cur = val + i * log(p[dep]);
    if (cur < rval) dfs(dep + 1, i, sum * (2 * i + 1), cur);
    cnt[dep] = 0;
  }
}

int main() {
  rval = 1e100;
  dfs(0, 2000000, 1, 0); 
  for (int i = 0; i < 12; ++i) {
    printf("%d^%d*", p[i], ret[i]);
  }
  puts("");
  return 0;
}
