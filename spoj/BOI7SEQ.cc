// http://www.spoj.com/problems/BOI7SEQ/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000000 + 10, inf = 1e9;
int Q[MAXN], top;

int main() {
  int n; scanf("%d", &n);
  long long ret = top = 0;
  Q[++ top] = inf;
  for (int i = 0, v; i <= n; ++ i) {
    if (i == n) v = inf;
    else scanf("%d", &v);
    while (top >= 1 && v >= Q[top]) {
      int add = min(v, Q[top - 1]);
      if (add == inf) break;
      ret += add, -- top;
    }
    Q[++ top] = v;
  }
  cout << ret << endl;
  return 0;
}
