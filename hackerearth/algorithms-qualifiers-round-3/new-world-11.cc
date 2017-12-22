#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 10;
int x[MAXN], f[MAXN], Q[MAXN], n, m;
typedef pair<int, int> PII;

bool check(int d) {
  int h = 1, t = 1;
  Q[1] = n - 1; f[n - 1] = 0;
  for (int i = n - 2, j = n - 1; i >= 0; -- i) {
    while (x[j] > x[i] + d) -- j;
    while (h <= t && Q[h] > j) ++ h;
    f[i] = 1 + f[Q[h]];
    while (h <= t && f[i] <= f[Q[t]]) -- t;
    Q[++ t] = i;
  }
  return f[0] <= m;
}

int sol() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++ i) scanf("%d", x + i);
  int l = 0, r = x[n - 1] - x[0];
  for (int i = 1; i < n; ++ i) l = max(l, x[i] - x[i - 1]);
  while (l < r) {
    int mid = (l + r - 1) >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }
  return l;
}

int main() {
  int T; scanf("%d", &T);
  while (T --) cout << sol() << endl;
  return 0;
}
