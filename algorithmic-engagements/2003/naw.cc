#include <cstdio>
#include <algorithm>

const int N = 30000 + 10;

struct Node {
  int val;
  int add;
  void apply(int v) {
    add += v;
    val += v;
  }
} T[N << 2];

char s[N];
int p[N];

void build(int o, int l, int r) {
  if (l + 1 == r) {
    T[o].val = p[l];
    return;
  }
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
  T[o].val = std::min(T[o << 1].val, T[o << 1 | 1].val);
}

void push(int o) {
  if (T[o].add) {
    T[o << 1].apply(T[o].add);
    T[o << 1 | 1].apply(T[o].add);
    T[o].add = 0;
  }
}

void modify(int o, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    T[o].apply(v);
    return;
  }
  push(o);
  int m = (l + r) >> 1;
  if (L < m) modify(o << 1, l, m, L, R, v);
  if (R > m) modify(o << 1 | 1, m, r, L, R, v);
  T[o].val = std::min(T[o << 1].val, T[o << 1 | 1].val);
}

int main() {
  int n;
  scanf("%d%s", &n, s);
  p[0] = s[0] == '(' ? 1 : -1;
  for (int i = 1; i < n; ++i) {
    p[i] = p[i - 1] + (s[i] == '(' ? 1 : -1);
  }
  build(1, 0, n);
  int m;
  scanf("%d", &m);
  int cnt = p[n - 1];
  for (int i = 0; i < m; ++i) {
    int x;
    scanf("%d", &x);
    if (x == 0) puts(cnt == 0 && T[1].val == 0 ? "TAK" : "NIE");
    else {
      --x;
      int delta = s[x] == '(' ? -2 : 2;
      modify(1, 0, n, x, n, delta);
      cnt += delta;
      s[x] = '(' + ')' - s[x];
    }
  }
  return 0;
}
