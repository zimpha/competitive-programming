#include <bits/stdc++.h>
using LL = long long;

const int N = 100000 + 10, S = 1000 + 10;
int book[S][S], inv[S];
int sum[S];
std::vector<int> G[N];
int n, m, q;

struct query {
  int op;
  int i, j, k;
  int ans;
} ask[N];

void dfs(int u, int now = 0) {
  int c1, c2;
  int x = ask[u].i, y = ask[u].j;
  if (u != 0) {
    c2 = sum[x];
    now -= sum[x];
    if (ask[u].op == 1) {
      c1 = book[x][y];
      if (!(inv[x] ^ book[x][y])) book[x][y] = !inv[x], sum[x]++;
    } else if (ask[u].op == 2) {
      c1 = book[x][y];
      if (inv[x] ^ book[x][y]) book[x][y] = inv[x], sum[x]--;
    } else if (ask[u].op == 3) {
      c1 = inv[x];
      inv[x] ^= 1;
      sum[x] = m - sum[x];
    }
    now += sum[x];
  }
  ask[u].ans = now;
  for (auto &&v: G[u]) dfs(v, now);
  if (u != 0) {
    sum[x] = c2;
    if (ask[u].op == 1) book[x][y] = c1;
    else if (ask[u].op == 2) book[x][y] = c1;
    else if (ask[u].op == 3) inv[x] = c1;
  }
}

void run() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d", &ask[i].op);
    if (ask[i].op <= 2) {
      scanf("%d%d", &ask[i].i, &ask[i].j);
    } else if (ask[i].op == 3) {
      scanf("%d", &ask[i].i);
    } else {
      scanf("%d", &ask[i].k);
    }
    if (ask[i].op == 4) {
      G[ask[i].k].push_back(i);
    } else {
      G[i - 1].push_back(i);
    }
  }
  dfs(0);
  for (int i = 1; i <= q; ++i) {
    printf("%d\n", ask[i].ans);
  }
}

int main() {
  run();
  return 0;
}
