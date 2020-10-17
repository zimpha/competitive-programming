#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e6 + 10;

int mx[N << 2];
std::vector<int> qs[N];
int a[N], L[N], ret[N];

void ins(int o, int l, int r, int x, int v) {
  if (l + 1 == r) {
    mx[o] = v;
    return;
  }
  int m = (l + r) >> 1;
  if (x < m) ins(o << 1, l, m, x, v);
  else ins(o << 1 | 1, m, r, x, v);
  mx[o] = std::min(mx[o << 1], mx[o << 1 | 1]);
}

int query(int o, int l, int r, int bound) {
  //printf("l=%d r=%d mx=%d bound=%d\n", l, r, mx[o], bound);
  if (l + 1 == r) return l;
  int m = (l + r) >> 1;
  if (mx[o << 1] >= bound) return query(o << 1 | 1, m, r, bound);
  else return query(o << 1, l, m, bound);
}

int main() {
  int n, q;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  scanf("%d", &q);
  for (int i = 0, r; i < q; ++i) {
    scanf("%d%d", &L[i], &r);
    qs[r].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    ins(1, 0, N, a[i], i);
    for (auto &e: qs[i]) {
      ret[e] = query(1, 0, N, L[e]);
    }
  }
  for (int i = 0; i < q; ++i) printf("%d\n", ret[i]);
  return 0;
}
