#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;

struct Node {
  std::vector<int64> s;
  int m;
  void init() {
    s.clear();
    m = 0;
  }
  void add(int64 x) {
    m++; s.push_back(x);
    while (m >= 3 && s[m - 3] <= s[m - 2] && s[m - 2] >= s[m - 1]) {
      s[m - 3] = s[m - 3] - s[m - 2] + s[m - 1];
      s.pop_back(); s.pop_back();
      m -= 2;
    }
  }
  int64 value() {
    int l = 0, r = m - 1, z = 0;
    int64 delta = 0;
    for (; z < m; ++z) {
      assert(l <= r);
      auto u = (s[l] > s[r]) ? s[l++] : s[r--];
      if (z & 1) delta -= u;
      else delta += u;
    }
    return delta;
  }
} T[N << 2], buf;

void ins(int o, int l, int r, int x, int v) {
  T[o].add(v);
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  if (x < m) ins(o << 1, l, m, x, v);
  else ins(o << 1 | 1, m, r, x, v);
}

void get(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) {
    for (auto &x: T[o].s) buf.add(x);
    return;
  }
  int m = (l + r) >> 1;
  if (L < m) get(o << 1, l, m, L, R);
  if (R > m) get(o << 1 | 1, m, r, L, R);
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int64> s(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &s[i]);
    ins(1, 0, n, i, s[i]);
    if (i) s[i] += s[i - 1];
  }
  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    buf.init();
    get(1, 0, n, l - 1, r);
    auto sum = s[r - 1] - (l == 1 ? 0 : s[l - 2]);
    auto delta = buf.value();
    printf("%lld %lld\n", (delta + sum) / 2, (sum - delta) / 2);
  }
  return 0;
}
