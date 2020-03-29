#include <cstdio>
#include <vector>

using int64 = long long;

struct FenwickTree {
  std::vector<int64> u;
  int n, base;
  void init(int n) {
    this->base = n + 1;
    this->n = n * 2 + 1;
    u.resize(this->n + 1, 0);
  }
  void add(int x, int64 v) {
    for (x += base; x <= n; x += ~x & x + 1) u[x] += v;
  }
  int64 get(int x, int64 r = 0) {
    for (x += base; x >= 0; x -= ~x & x + 1) r += u[x];
    return r;
  }
} f, g, tag1, tag2;

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  std::vector<int> ql(q), qr(q);
  std::vector<std::vector<int>> query(n + 1);
  for (int i = 0, t; i < q; ++i) {
    scanf("%d%d%d", &t, &ql[i], &qr[i]);
    --ql[i], --qr[i];
    query[t].push_back(i);
  }

  std::vector<int> ml(n), mr(n);
  for (int i = 0; i < n; ++i) {
    int j = i == 0 ? -1 - n : i - 1;
    while (j >= 0 && a[j] <= a[i]) j = ml[j];
    ml[i] = j;
  }
  for (int i = n - 1; i >= 0; --i) {
    int j = i + 1;
    while (j < n && a[j] < a[i]) j = mr[j];
    mr[i] = j;
  }

  std::vector<int> tl, tr, tw;
  std::vector<std::vector<int>> remove(n + 1);
  // i * g + f is prefix sum
  f.init(n); g.init(n);
  tag1.init(n); tag2.init(n);

  auto add = [&](int l, int r, int64 w) { // [l, r)
    if (r - l <= n) remove[r - l].push_back(tl.size());
    tl.push_back(l); tr.push_back(r); tw.push_back(w);
    f.add(l, w * (1 - l)); f.add(r, -w * (1 - r));
    g.add(l, w); g.add(r, -w);
    tag1.add(l, w); tag2.add(l, w * (1 - l));
  };

  for (int i = 0; i < n; ++i) {
    add(ml[i] + 1, mr[i], a[i]);
    if (ml[i] + 1 < i) add(ml[i] + 1, i, -a[i]);
    if (i + 1 < mr[i]) add(i + 1, mr[i], -a[i]);
  }

  auto ask = [&](int x, int t) {
    //printf("x=%d t=%d f=%lld g=%lld t1(x-t)=%lld t2(x-t)=%lld t1(x)=%lld t2(x)=%lld\n", x, t, f.get(x), g.get(x), tag1.get(x - t), tag2.get(x - t), tag1.get(x), tag2.get(x));
    return f.get(x) + x * g.get(x) + (x - t) * tag1.get(x - t) + tag2.get(x - t) - x * tag1.get(x) - tag2.get(x);
  };

  std::vector<int64> ret(q);
  for (int i = 1; i <= n; ++i) {
    for (auto &e: remove[i]) {
      int l = tl[e], r = tr[e];
      int64 w = tw[e];
      f.add(l, -w * (1 - l)); f.add(r, w * (1 - r));
      g.add(l, -w); g.add(r, w);
      tag1.add(l, -w); tag2.add(l, -w * (1 - l));
    }
    for (auto &e: query[i]) {
      ret[e] = ask(qr[e], i) - ask(ql[e] - 1, i);
    }
  }
  for (int i = 0; i < q; ++i) printf("%lld\n", ret[i]);
  return 0;
}
