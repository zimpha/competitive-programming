#include <cstdio>
#include <vector>
#include <cassert>
#include <set>
#include <algorithm>

const int N = 2e5 + 10;

using int64 = long long;

struct SegmentTree {
  int64 sum[N << 2], mx[N << 2];
  int64 delta[N << 2];
  void apply(int o, int l, int r, int v) {
    delta[o] = mx[o] = v;
    sum[o] = int64(v) * (r - l + 1);
  }
  void push(int o, int l, int r) {
    if (delta[o] != -1) {
      int m = (l + r) >> 1;
      apply(o << 1, l, m, delta[o]);
      apply(o << 1 | 1, m + 1, r, delta[o]);
      delta[o] = -1;
    }
  }
  void update(int o) {
    sum[o] = sum[o << 1] + sum[o << 1 | 1];
    mx[o] = std::max(mx[o << 1], mx[o << 1 | 1]);
  }
  void build(int o, int l, int r) {
    delta[o] = -1;
    if (l == r) {
      mx[o] = sum[o] = l;
      return;
    }
    int m = (l + r) >> 1;
    build(o << 1, l, m);
    build(o << 1 | 1, m + 1, r);
    update(o);
  }
  int get(int o, int l, int r, int x) {
    if (l == r) return sum[o];
    push(o, l, r);
    int m = (l + r) >> 1;
    if (x <= m) return get(o << 1, l, m, x);
    else return get(o << 1 | 1, m + 1, r, x);
  }
  int64 get(int o, int l, int r, int L, int R) {
    if (L <= l && R >= r) return sum[o];
    push(o, l, r);
    int64 ret = 0;
    int m = (l + r) >> 1;
    if (L <= m) ret += get(o << 1, l, m, L, R);
    if (R > m) ret += get(o << 1 | 1, m + 1, r, L, R);
    return ret;
  }
  void set(int o, int l, int r, int L, int R, int w) {
    if (L <= l && R >= r) {
      apply(o, l, r, w);
      return;
    }
    push(o, l, r);
    int m = (l + r) >> 1;
    if (L <= m) set(o << 1, l, m, L, R, w);
    if (R > m) set(o << 1 | 1, m + 1, r, L, R, w);
    update(o);
  }
  // first position >= x
  int lower_bound(int o, int l, int r, int x) {
    if (l == r) return l;
    push(o, l, r);
    int m = (l + r) >> 1;
    if (mx[o << 1] < x) return lower_bound(o << 1 | 1, m + 1, r, x);
    else return lower_bound(o << 1, l, m, x);
  }
} min_pre, min_i;

int a[N], prev[N], next[N], last[N];
int n;

// sum from l to r with value < w
int64 get_sum_i(int l, int r, int64 w) {
  int p = min_i.mx[1] < w ? n + 1 : min_i.lower_bound(1, 1, n, w);
  if (p > r) return min_i.get(1, 1, n, l, r);
  else if (p <= l) return w * (r - l + 1);
  else return min_i.get(1, 1, n, l, p - 1) + w * (r - p + 1);
}

// sum from l to r with value >= w
int64 get_sum_pre(int l, int r, int64 w) {
  int p = min_pre.mx[1] < w ? n + 1 : min_pre.lower_bound(1, 1, n, w);
  if (p <= l) return min_pre.get(1, 1, n, l, r);
  else if (p > r) return w * (r - l + 1);
  else return min_pre.get(1, 1, n, p, r) + w * (p - l);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  for (int i = 1; i <= n; ++i) last[i] = 0;
  for (int i = 1; i <= n; ++i) {
    prev[i] = last[a[i]];
    last[a[i]] = i;
  }
  for (int i = 1; i <= n; ++i) last[i] = n + 1;
  for (int i = n; i >= 1; --i) {
    next[i] = last[a[i]];
    last[a[i]] = i;
  }
  long long ret = 0, sum = 0;
  min_pre.build(1, 1, n);
  min_i.build(1, 1, n);
  std::vector<std::pair<int, int>> queue;
  std::set<int> indices;
  for (int i = 1; i <= n; ++i) indices.insert(i);
  for (int k = 2; k <= n; ++k) {
    while (!queue.empty() && queue.back().second >= prev[k]) {
      int r = queue.back().first, w = queue.back().second;
      queue.pop_back();
      int l = queue.empty() ? 1 : queue.back().first + 1;
      sum -= (int64)w * (r - l + 1) - get_sum_i(l, r, w);
    }
    int l = queue.empty() ? 1 : queue.back().first + 1;
    int r = k - 1;
    queue.emplace_back(k - 1, prev[k]);
    sum += (int64)prev[k] * (r - l + 1) - get_sum_i(l, r, prev[k]);
    min_pre.set(1, 1, n, l, r, prev[k]);
    if (prev[k]) {
      assert(indices.count(prev[k]));
      indices.erase(prev[k]);
      auto it = indices.lower_bound(prev[k]);
      assert(it != indices.end());
      int u = prev[k] == 1 ? 0 : min_i.get(1, 1, n, prev[k] - 1);
      int v = min_i.get(1, 1, n, prev[k]);
      int l = prev[k], r = *it - 1;
      sum -= get_sum_pre(l, r, v) - (int64)v * (r - l + 1);
      min_i.set(1, 1, n, l, r, u);
      sum += get_sum_pre(l, r, u) - (int64)u * (r - l + 1);
    }
    ret += sum;
  }
  printf("%lld\n", ret);
  return 0;
}
