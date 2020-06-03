#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using int64 = long long;
using pii = std::pair<int, int>;

const int S = 3e5 * 2 * 4 + 10;

struct Node {
  int max, tag;
  void mark(int v) {
    tag += v;
    max += v;
  }
} T[S];

void build(int o, int l, int r) {
  T[o].tag = T[o].max = 0;
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  build(o << 1, l, m);
  build(o << 1 | 1, m, r);
}

void pushdown(int o) {
  T[o << 1].mark(T[o].tag);
  T[o << 1 | 1].mark(T[o].tag);
  T[o].tag = 0;
}

void add(int o, int l, int r, int L, int R, int v) {
  if (L <= l && R >= r) {
    T[o].mark(v);
    return;
  }
  pushdown(o);
  int m = (l + r) >> 1;
  if (L < m) add(o << 1, l, m, L, R, v);
  if (R > m) add(o << 1 | 1, m, r, L, R, v);
  T[o].max = std::max(T[o << 1].max, T[o << 1 | 1].max);
}

int ask(int o, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[o].max;
  pushdown(o);
  int m = (l + r) >> 1, ret = -1e9;
  if (L < m) ret = std::max(ret, ask(o << 1, l, m, L, R));
  if (R > m) ret = std::max(ret, ask(o << 1 | 1, m, r, L, R));
  T[o].max = std::max(T[o << 1].max, T[o << 1 | 1].max);
  return ret;
}

void print(int o, int l, int r) {
  if (l + 1 == r) {
    printf("%d ", T[o].max);
    return;
  }
  pushdown(o);
  int m = (l + r) >> 1;
  print(o << 1, l, m);
  print(o << 1 | 1, m, r);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int N, K;
    int64 X, A, B, M, p, q;
    scanf("%d%d%lld%lld%lld%lld%lld%lld", &N, &K, &X, &A, &B, &M, &p, &q);
    auto next = [&]() {
      X = ((int64)A * X + B) % M;
      return X;
    };
    std::vector<int64> aa(N), bb(N), cc(N), dd(N);
    for (int i = 0; i < K; ++i) {
      scanf("%lld%lld%lld%lld", &aa[i], &bb[i], &cc[i], &dd[i]);
    }
    for (int i = K; i < N; ++i) {
      aa[i] = aa[i - K] + next() % (2 * p) - p;
      bb[i] = aa[i] + 1 + next() % (2 * (bb[i % K] - aa[i % K]));
      cc[i] = cc[i - K] + next() % (2 * q) - q;
      dd[i] = cc[i] + 1 + next() % (2 * (dd[i % K] - cc[i % K]));
    }
    std::vector<int64> a(N), b(N), c(N), d(N);
    std::vector<int64> xs(N * 2), ys(N * 2);
    for (int i = 0; i < N; i++) {
      xs[i * 2] = a[i] = aa[i] * 1000000 + i;
      xs[i * 2 + 1] = b[i] = bb[i] * 1000000 + i;
      ys[i * 2] = c[i] = cc[i] * 1000000 + i;
      ys[i * 2 + 1] = d[i] = dd[i] * 1000000 + i;
    }
    std::sort(xs.begin(), xs.end());
    std::sort(ys.begin(), ys.end());
    for (int i = 0; i < N; ++i) {
      a[i] = std::lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
      b[i] = std::lower_bound(xs.begin(), xs.end(), b[i]) - xs.begin();
      c[i] = std::lower_bound(ys.begin(), ys.end(), c[i]) - ys.begin();
      d[i] = std::lower_bound(ys.begin(), ys.end(), d[i]) - ys.begin();
      //printf("%d: %d %d %d %d\n", i, (int)a[i], (int)b[i], (int)c[i], (int)d[i]);
    }
    build(1, 0, N * 2);
    std::set<int> right, left;
    int ret = -1;
    std::vector<std::pair<int, int>> event;
    for (int i = 0; i < N; ++i) {
      if (c[i]) add(1, 0, N * 2, 0, c[i], 1);
      //printf("inc %d\n", (int)c[i]);
      right.insert(c[i]);
      event.emplace_back(a[i], +i + 1);
      event.emplace_back(b[i], -i - 1);
    }
    std::sort(event.begin(), event.end());
    for (auto &&ev : event) {
      if (ev.second > 0) {
        int ed = c[ev.second - 1];
        right.erase(ed);
        if (ed) add(1, 0, N * 2, 0, ed, -1);
        //printf("dec %d\n", ed);
        //printf("erase right %d %d\n", ev.second - 1, ed);
        //print(1, 0, N * 2); puts("");
      } else {
        int ed = d[-ev.second - 1];
        left.insert(ed);
        add(1, 0, N * 2, ed, N * 2, 1);
        //printf("add left %d %d\n", -ev.second - 1, ed);
        //print(1, 0, N * 2); puts("");
        if (!left.empty() && !right.empty()) {
          int l = *left.begin(), r = *right.rbegin();
          if (l < r) {
            ret = std::max<int>(ret, ask(1, 0, N * 2, l, r));
            //printf("%d %d: %d\n", l, r, ask(1, 0, N * 2, l, r));
          }
        }
      }
    }
    if (ret != -1) ret = N - ret;
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}