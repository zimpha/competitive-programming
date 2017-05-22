#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 10;

int n, ans;
vector <int> edges[N];
int bts[N];

void DFS(int u, int p) {
  int msk = 0, val = 0;
  for (auto &&v: edges[u]) {
    if (v == p) continue;
    DFS(v, u);
    for (int b = val + 1; b < 20; b++) {
      if (((1 << b) & msk) && ((1 << b) & bts[v])) {
        val = b + 1;
      }
    }
    msk |= bts[v];
  }
  while ((1 << val) & msk) val++;
  bts[u] = 1 << val;
  for (int b = val + 1; b < 20; b++) {
    if ((1 << b) & msk) {
      bts[u] |= (1 << b);
    }
  }
  ans = max(ans, val);
}

int main() {
  scanf("%d", &n);
  for(int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    edges[x].push_back(y);
    edges[y].push_back(x);
  }
  DFS(1, 0);
  printf("%d\n", ans + 1);
  return 0;
}
