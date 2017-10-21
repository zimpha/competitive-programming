#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 300000 + 10;

int mx[N << 2], tag[N << 2];

inline void mark(int rt, int v) {
  mx[rt] += v;
  tag[rt] += v;
}

inline void push_down(int rt) {
  if (tag[rt] != 0) {
    mark(rt << 1, tag[rt]);
    mark(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
  }
}

void add(int rt, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    mark(rt, v);
    return;
  }
  int m = (l + r) >> 1;
  push_down(rt);
  if (L < m) add(rt << 1, l, m, L, R, v);
  if (R > m) add(rt << 1 | 1, m, r, L, R, v);
  mx[rt] = std::max(mx[rt << 1], mx[rt << 1 | 1]);
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> prev(n), pos(n, -1);
  int ret = 0;
  for (int i = 0, x; i < n; ++i) {
    scanf("%d", &x);
    --x;
    prev[i] = pos[x];
    pos[x] = i;
    add(1, 0, n, prev[i] + 1, i + 1, 1);
    if (prev[i] != -1) {
      add(1, 0, n, prev[prev[i]] + 1, prev[i] + 1, -1);
    }
    ret = std::max(ret, mx[1]);
  }
  printf("%d\n", ret);
  return 0;
}
