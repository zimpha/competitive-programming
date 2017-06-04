#include <bits/stdc++.h>
using namespace std;
typedef double flt;
typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 50000 + 10;
int a[MAXN], b[MAXN], n, ret;

void solve(int g) {
  int s = 0, cnt = 0;
  for (int i = 1; i < n; ++i) {
    if (a[i] % g) s = __gcd(s, a[i]), ++cnt;
  }
  if (cnt == 0) ret = max(ret, g);
  else ret = max(ret, min(s, g));
}

void run() {
  scanf("%d", &n); ret = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
  }
  for (int x = 1; x * x <= a[0]; ++x) if (a[0] % x == 0) {
    solve(x); solve(a[0] / x);
  }
  printf("%d\n", ret);
}

int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) run();
  return 0;
}
