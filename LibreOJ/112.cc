#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 2e5 + 10;

struct triple {
  int a, b, c;
  int cnt, ret;
  bool operator < (const triple &rhs) const {
    return a < rhs.a || (a == rhs.a && b < rhs.b) || (a == rhs.a && b == rhs.b && c < rhs.c);
  }
  bool operator != (const triple &rhs) const {
    return a != rhs.a || b != rhs.b || c != rhs.c;
  }
} p[N], q[N];

int bit[N], n, m;


void add(int x, int v) {
  for (; x <= m; x += ~x & x + 1) bit[x] += v;
}

void init(int x) {
  for (; x <= m; x += ~x & x + 1) bit[x] = 0;
}

int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += bit[x];
  return r;
}

void solve(int l, int r) {
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  solve(l, m);
  solve(m, r);
  int x = l, y = m;
  for (int i = l; i < r; ++i) {
    if (y >= r || (x < m && p[x].b <= p[y].b)) {
      q[i] = p[x++];
      add(q[i].c, q[i].cnt);
    } else {
      q[i] = p[y++];
      q[i].ret += get(q[i].c);
    }
  }
  for (int i = l; i < r; ++i) {
    p[i] = q[i];
    init(p[i].c);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
  }
  std::sort(p, p + n);
  int k = 0;
  for (int i = 0, cnt = 0; i < n; ++i) {
    ++cnt;
    if (p[i] != p[i + 1]) {
      p[k] = p[i];
      p[k++].cnt = cnt;
      cnt = 0;
    }
  }
  solve(0, k);
  std::vector<int> res(n);
  for (int i = 0; i < k; ++i) {
    res[p[i].ret + p[i].cnt - 1] += p[i].cnt;
  }
  for (int i = 0; i < n; ++i) {
    printf("%d\n", res[i]);
  }
  return 0;
}
