#include <cstdio>
#include <vector>
#include <algorithm>

int dis(int l, int r) {
  return (r - l + 1000000) % 1000000;
}

bool inside(int l, int r, int o) {
  return dis(l, o) + dis(o, r) == dis(l, r);
}

struct point {
  int x, y, c;
  point(int x, int y, int c): x(x), y(y), c(c) {}
  bool operator < (const point &rhs) const {
    return x > rhs.x || (x == rhs.x && y > rhs.y);
  }
};

struct SegTree {
  static const int N = 3000 + 10;
  int val[N << 2], lazy[N << 2];
  void build(int o, int l, int r) {
    val[o] = lazy[o] = 0;
    if (l + 1 == r) return;
    int m = (l + r) >> 1;
    build(o << 1, l, m);
    build(o << 1 | 1, m, r);
  }
  void apply(int o, int v) {
    lazy[o] += v;
    val[o] += v;
  }
  void update(int o) {
    val[o] = std::min(val[o << 1], val[o << 1 | 1]);
  }
  void push(int o) {
    if (lazy[o]) {
      apply(o << 1, lazy[o]);
      apply(o << 1 | 1, lazy[o]);
      lazy[o] = 0;
    }
  }
  void add(int o, int l, int r, int L, int R) {
    if (L <= l && R >= r) {
      apply(o, 1);
      return;
    }
    push(o);
    int m = (l + r) >> 1;
    if (L < m) add(o << 1, l, m, L, R);
    if (R > m) add(o << 1 | 1, m, r, L, R);
    update(o);
  }
  int lower(int o, int l, int r, int v) {
    if (l + 1 == r) return l;
    push(o);
    int m = (l + r) >> 1;
    if (val[o << 1 | 1] <= v) return lower(o << 1 | 1, m, r, v);
    else return lower(o << 1, l, m, v);
  }
  int get(int o, int l, int r, int x) {
    if (l + 1 == r) return val[o];
    push(o);
    int m = (l + r) >> 1;
    if (x < m) return get(o << 1, l, m, x);
    else return get(o << 1 | 1, m, r, x);
  }
} seg;

std::vector<int> ys;
int solve(std::vector<point> &pts) {
  ys.clear(); ys.reserve(pts.size());
  for (auto &p: pts) ys.push_back(p.y);
  std::sort(ys.begin(), ys.end());
  ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
  std::sort(pts.begin(), pts.end());
  int m = ys.size();
  if (m == 0) return 0;
  seg.build(1, 0, m);
  for (auto &p: pts) {
    int y = std::lower_bound(ys.begin(), ys.end(), p.y) - ys.begin();
    if (p.c == 0) {
      seg.add(1, 0, m, y, m);
    } else {
      int v = seg.get(1, 0, m, y);
      int p = seg.lower(1, 0, m, v);
      seg.add(1, 0, m, 0, p + 1);
    }
  }
  return seg.get(1, 0, m, m - 1);
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) scanf("%d%d", &l[i], &r[i]);
    int ret = 0;
    std::vector<point> pts;
    pts.reserve(n);
    for (int i = 0; i < n; ++i) {
      int lenlr = dis(l[i], r[i]);
      int lenrl = dis(r[i], l[i]);
      int extra = 0;
      for (int j = 0; j < n; ++j) {
        bool left = inside(l[j], r[j], l[i]);
        bool right = inside(l[j], r[j], r[i]);
        if (left && right) ++extra;
        else if (left) pts.emplace_back(dis(l[i], r[j]), dis(l[j], l[i]), 1);
        else if (right) pts.emplace_back(lenlr - dis(l[j], r[i]), lenrl - dis(r[i], r[j]), 0);
      }
      ret = std::max(ret, extra + solve(pts));
      pts.clear();
    }
    printf("%d\n", ret);
  }
  return 0;
}
