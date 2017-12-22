#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 100000 + 10;

int a[MAXN], n, c;

int main() {
  scanf("%d%d", &n, &c);
  for (int i = 0; i < n; ++ i) scanf("%d", a + i);
  sort(a, a + n);
  for (int i = 0; i < n / 2; ++ i) a[i] -= c, a[n - i - 1] += c;
  LL sum(0), ret(0);
  for (int i = 0; i < n; ++ i) sum += a[i];
  for (int i = 0; i < n; ++ i) {
    ret += sum - 1ll * a[i] * (n - i);
    sum -= a[i];
  }
  cout << ret << endl;
  return 0;
}
