#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100000 + 10;
int P[MAXN], Q[MAXN], A[MAXN];
int dsu[MAXN], n, m;

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

void sol() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++ i) scanf("%d", P + i);
  for (int i = 1; i <= n; ++ i) scanf("%d", Q + i);
  for (int i = 1; i <= n; ++ i) dsu[i] = i;
  for (int i = 0; i < m; ++ i) {
    int u, v; scanf("%d%d", &u, &v);
    u = get(u), v = get(v);
    dsu[u] = v;
  }
  for (int i = 1; i <= n; ++ i) A[Q[i]] = i;
  for (int i = 1; i <= n; ++ i) Q[i] = A[P[i]];
  for (int i = 1; i <= n; ++ i) if (Q[i]) {
    int fa = get(i);
    for (int j = i; Q[j];) {
      if (fa != get(j)) {
        puts("NO");
        return;
      }
      int k = Q[j]; Q[j] = 0; j = k;
    }
  }
  puts("YES");
}

int main() {
  int T; scanf("%d", &T);
  while (T --) sol();
  return 0;
}
