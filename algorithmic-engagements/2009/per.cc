#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10;

struct Node {
  int mx, delta;
  void apply(int d) {
    mx += d;
    delta += d;
  }
} T[N << 2];

void update(int o) {
  T[o].mx = std::max(T[o << 1].mx, T[o << 1 | 1].mx);
}

void push(int o) {
  if (T[o].delta) {
    T[o << 1].apply(T[o].delta);
    T[o << 1 | 1].apply(T[o].delta);
    T[o].delta = 0;
  }
}

void build(int o, int l, int r, std::vector<int> &cnt) {
  if (l + 1 == r) {
    T[o].mx = cnt[l] - r;
    return;
  }
  int m = (l + r) >> 1;
  if (l < m) build(o << 1, l, m, cnt);
  if (r > m) build(o << 1 | 1, m, r, cnt);
  update(o);
}

void add(int o, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    T[o].apply(v);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) add(o << 1, l, m, L, R, v);
  if (R > m) add(o << 1 | 1, m, r, L, R, v);
  update(o);
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> cnt(n), a(n);
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    cnt[x - 1]++;
    a[i] = x - 1;
  }
  for (int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
  build(1, 0, n, cnt);
  puts(T[1].mx <= 0 ? "TAK" : "NIE");
  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    int p, x;
    scanf("%d%d", &p, &x);
    --p, --x;
    add(1, 0, n, a[p], n, -1);
    a[p] = x;
    add(1, 0, n, a[p], n, +1);
    puts(T[1].mx <= 0 ? "TAK" : "NIE");
  }
  return 0;
}
