#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

const int N = 300000 + 10;

std::vector<int> ql[N];
int a[N], xs[N];
int n, m, q;

int mx[N << 2];

void ins(int rt, int l, int r, int x, int v) {
  mx[rt] = std::max(mx[rt], v);
  if (l + 1 == r) return;
  int mid = (l + r) >> 1;
  if (x < mid) ins(rt << 1, l, mid, x, v);
  else ins(rt << 1 | 1, mid, r, x, v);
}

int query(int rt, int l, int r, int x, int v) {
  if (mx[rt] < v) return -1;
  if (l + 1 == r) return l;
  int mid = (l + r) >> 1, ret = -1;
  if (mid < x) ret = query(rt << 1 | 1, mid, r, x, v);
  if (ret != -1) return ret;
  return query(rt << 1, l, mid, x, v);
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    xs[i] = a[i];
  }
  std::sort(xs, xs + n);
  m = std::unique(xs, xs + n) - xs;
  std::vector<int> l(q), r(q), h(q), ret(q);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d%d", &l[i], &r[i], &h[i]);
    h[i] = std::upper_bound(xs, xs + m, h[i]) - xs;
    ql[r[i]].emplace_back(i);
  }
  memset(mx, -1, sizeof(mx));
  for (int i = 0; i < n; ++i) {
    a[i] = std::lower_bound(xs, xs + m, a[i]) - xs;
    ins(1, 0, m, a[i], i);
    for (auto &&q: ql[i]) {
      if (!h[q]) ret[q] = -1;
      else ret[q] = query(1, 0, m, h[q], l[q]);
      if (ret[q] != -1) ret[q] = xs[ret[q]];
      else ret[q] = 0;
    }
  }
  for (int i = 0; i < q; ++i) {
    printf("%d\n", ret[i]);
  }
  return 0;
}
