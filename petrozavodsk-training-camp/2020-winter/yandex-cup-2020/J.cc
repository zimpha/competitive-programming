#include <cstdio>

const int N = 1e6 + 10;

int delta[N], dp[N], n;

void add(int x, int v) {
  for (; x <= n; x += ~x & x + 1) delta[x] += v;
}

int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += delta[x];
  return r;
}

void clear(int x) {
  int v = get(x);
  add(x, -v);
  add(x + 1, v);
  if (dp[x] == -1) return;
  dp[x] += v;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) dp[i] = -1;
  dp[1] = 0;
  for (int i = 0; i < n; ++i) {
    int op, p, q;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d", &p);
      clear(p); dp[p] = 0;
      add(0, 1); add(p, -1);
      add(p + 1, 1);
    } else {
      scanf("%d%d", &p, &q);
      clear(p); clear(q);
      if (dp[p] != -1 && (dp[q] == -1 || dp[p] < dp[q])) dp[q] = dp[p];
      if (dp[p] != -1) dp[p]++;
    }
  }
  for (int i = 0; i <= n; ++i) clear(i);
  for (int i = 1; i <= n; ++i) printf("%d ", dp[i]);
  puts("");
  return 0;
}
