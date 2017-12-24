#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <functional>

using int64 = long long;
using pii = std::pair<int, int>;

constexpr int N = 1e5 + 10;
constexpr int M = 1e5 + 10;
constexpr int K = 16;

struct query_t {
  int l, r, t;
} ask[N];

std::vector<int> query[60][60];
int a[N], value[N];
int angry[N];
int n, q, B;

namespace mo {
  int cnt[M], mark[N];
  int64 ret;
  void init() {
    memset(cnt, 0, sizeof(cnt));
    memset(mark, 0, sizeof(mark));
    ret = 0;
  }
  void add(int x) {
    int v = value[x];
    if (mark[x]) ret -= (int64)v * angry[cnt[v]--];
    else ret += (int64)v * angry[++cnt[v]];
    mark[x] ^= 1;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &angry[i]);
  }

  for (B = 1; B * B * B < n; ++B);
  B = B * B;
  std::vector<pii> modify;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int op, x, y;
    scanf("%d%d%d", &op, &x, &y);
    if (op == 2) {
      ask[i].t = -2;
      modify.emplace_back(x - 1, y);
    } else {
      --x, --y;
      ask[i].t = modify.size() - 1;
      ask[i].l = x;
      ask[i].r = y;
      query[x / B][y / B].emplace_back(i);
    }
  }
  std::vector<int64> ret(q);
  int m = (n - 1) / B + 1;
  for (int i = 0; i < m; ++i) {
    for (int j = i; j < m; ++j) {
      if (query[i][j].empty()) continue;
      memcpy(value, a, sizeof(*a) * n);
      mo::init();
      int t = 0, l = 0, r = -1;
      for (auto &&v: query[i][j]) {
        auto qr = ask[v];
        while (r < qr.r) mo::add(++r);
        while (r > qr.r) mo::add(r--);
        while (l < qr.l) mo::add(l++);
        while (l > qr.l) mo::add(--l);
        for (int x, y; t <= qr.t; ++t) {
          std::tie(x, y) = modify[t];
          bool flag = qr.l <= x && x <= qr.r;
          if (flag) mo::add(x);
          value[x] = y;
          if (flag) mo::add(x);
        }
        ret[v] = mo::ret;
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    if (ask[i].t == -2) continue;
    printf("%lld\n", ret[i]);
  }
  return 0;
}
