#include <cstdio>
#include <cassert>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

using ll = long long;

const int N = 100000 + 10;
const ll inf = 8333583335000000000ll;

int a[N], cov[N], sum_rank[N], n;
ll sum[N], max_sum[N], min_sum[N];
ll m;

struct SegmentTree {
  struct node {
    ll mi, mx;
  } data[N << 2];
  node merge(const node &a, const node &b) {
    node c;
    c.mi = std::min(a.mi, b.mi);
    c.mx = std::max(a.mx, b.mx);
    return c;
  }
  void build(int rt, int l, int r) {
    if (l + 1 == r) {
      data[rt].mx = data[rt].mi = sum[l];
      return;
    }
    int m = (l + r) >> 1;
    build(rt << 1, l, m);
    build(rt << 1 | 1, m, r);
    data[rt] = merge(data[rt << 1], data[rt << 1 | 1]);
  }
  node ask(int rt, int l, int r, int L, int R) {
    if (L <= l && R >= r) return data[rt];
    int m = (l + r) >> 1;
    node ret{inf, -inf};
    if (L < m) ret = merge(ret, ask(rt << 1, l, m, L, R));
    if (R > m) ret = merge(ret, ask(rt << 1 | 1, m, r, L, R));
    return ret;
  }
} st;

ll get(int l, int r) {
  auto res = st.ask(1, 0, n, l + 1, r + 1);
  return res.mi - res.mx;
}

namespace treap {
  struct node {
    int sz, i, mx;
    ll val, sum;
    node *l, *r;
    node() = default;
    node(int i, ll v): sz(1), i(i), mx(i), val(v), sum(v), l(0), r(0) {}
    node* update() {
      sz = 1, mx = i, sum = val;
      if (l) sz += l->sz, mx = std::max(mx, l->mx), sum += l->sum;
      if (r) sz += r->sz, mx = std::max(mx, r->mx), sum += r->sum;
      return this;
    }
  } pool[N], *p, *rt;
  node* new_node(int i, ll v) {
    *p = node(i, v);
    return p++;
  }
  void init() {
    p = pool;
    rt = new_node(n, 0);
  }
  bool random(int a, int b) {
    return rand() % (a + b) < a;
  }
  node* merge(node *l, node *r) {
    if (!l || !r) return l ? l : r;
    if (random(l->sz, r->sz)) {
      l->r = merge(l->r, r);
      return l->update();
    } else {
      r->l = merge(l, r->l);
      return r->update();
    }
  }
  std::pair<node*, node*> split(node *o, ll v) {//(-inf, v], [v + 1, inf)
    node *l = 0, *r = 0;
    if (!o) return {l, r};
    if (o->val <= v) {
      std::tie(o->r, r) = split(o->r, v);
      l = o;
    } else {
      std::tie(l, o->l) = split(o->l, v);
      r = o;
    }
    o->update();
    return {l, r};
  }
  std::pair<node*, node*> split_by_size(node *o, int sz) {//(-inf, sz], [v + 1, inf)
    node *l = 0, *r = 0;
    if (!o) return {l, r};
    int ls = o->l ? o->l->sz : 0;
    if (ls + 1 <= sz) {
      std::tie(o->r, r) = split_by_size(o->r, sz - ls - 1);
      l = o;
    } else {
      std::tie(l, o->l) = split_by_size(o->l, sz);
      r = o;
    }
    o->update();
    return {l, r};
  }
  int rank(ll v) {// number of elements <= v
    node *a, *b;
    std::tie(a, b) = split(rt, v);
    int ret = a ? a->sz : 0;
    rt = merge(a, b);
    return ret;
  }
  void add(int i, ll v) {
    node *a, *b, *p = new_node(i, v);
    std::tie(a, b) = split(rt, v);
    rt = merge(a, merge(p, b));
  }
}

namespace kth {
  std::multiset<ll> A, B;
  ll sum;
  int k;
  void init(int _k) {
    k = _k;
    sum = 0;
  }
  void fix() {
    while (A.size() > k) {
      ll u = *A.rbegin();
      A.erase(A.find(u));
      B.insert(u);
      sum -= u;
    }
    while (A.size() < k && B.size()) {
      ll u = *B.begin();
      B.erase(B.find(u));
      A.insert(u);
      sum += u;
    }
  }
  void add(ll v) {
    A.insert(v);
    sum += v;
    fix();
  }
  void del(ll v) {
    if (B.find(v) != B.end()) B.erase(B.find(v));
    else A.erase(A.find(v)), sum -= v;
    fix();
  }
  void reduce() {
    --k;
    fix();
  }
}

std::vector<ll> xs;
namespace fen {
int bit[N];
void init() {
  for (int i = 0; i < xs.size(); ++i) bit[i] = 0;
}
void add(int x, int v) {
  for (; x < xs.size(); x += ~x & x + 1) bit[x] += v;
}
int get(int x, int r = 0) {
  for (; x >= 0; x -= ~x & x + 1) r += bit[x];
  return r;
}
}

ll count_ge(ll bound) {
  fen::init();
  fen::add(sum_rank[n], 1);
  ll ret = 0;
  for (int i = n - 1; i >= 0; --i) {
    int v = std::upper_bound(xs.begin(), xs.end(), sum[i] - bound) - xs.begin() - 1;
    ret += fen::get(v);
    fen::add(sum_rank[i], 1);
  }
  return ret;
}

ll find_border_sum(ll m) {
  ll delta = -5000000000ll - 1;
  ll left = 0, right = 100000000000ll;
  while (left < right) {
    ll mid = (left + right + 1) >> 1;
    if (count_ge(mid + delta) >= m) left = mid;
    else right = mid - 1;
  }
  return delta + left;
}

void trans(treap::node *o, std::vector<std::pair<int, int>> &pt, int upp, int l) {
  if (pt.size() == upp) return;
  if (!o) return;
  pt.emplace_back(l, o->i - 1);
  trans(o->l, pt, upp, l);
  trans(o->r, pt, upp, l);
}

int main() {
  scanf("%d%lld", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", a + i);
  }
  sum[n] = min_sum[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    sum[i] = sum[i + 1] + a[i];
    min_sum[i] = std::min(min_sum[i + 1], sum[i]);
    cov[i] = -1;
  }
  max_sum[0] = sum[0];
  for (int i = 1; i <= n; ++i) {
    max_sum[i] = std::max(max_sum[i - 1], sum[i]);
  }
  xs.assign(n + 1, 0);
  for (int i = 0; i <= n; ++i) xs[i] = sum[i];
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  for (int i = 0; i <= n; ++i) {
    sum_rank[i] = std::lower_bound(xs.begin(), xs.end(), sum[i]) - xs.begin();
  }
  st.build(1, 0, n);
  ll p = std::max<ll>(m - n, 0);
  ll q = m - p;
  ll sum1 = find_border_sum(p);
  ll sum2 = find_border_sum(m);
  ll pp = count_ge(sum1 + 1);
  ll qq = count_ge(sum2 + 1);
  ll slot = p - pp;
  std::vector<std::pair<int, int>> extra;
  ll ans1 = 0;
  treap::init();
  for (int i = n - 1; i >= 0; --i) {
    treap::node *a = 0, *b = 0, *c = 0;
    std::tie(b, c) = treap::split(treap::rt, sum[i] - sum1);
    std::tie(a, b) = treap::split(b, sum[i] - sum1 - 1);
    if (a) {
      cov[i] = std::max(cov[i], a->mx);
      ans1 += sum[i] * a->sz - a->sum;
    }
    if (b) {
      int need = std::min<ll>(slot, b->sz);
      treap::node *x, *y;
      std::tie(x, y) = split_by_size(b, need);
      if (x) {
        cov[i] = std::max(cov[i], x->mx);
        ans1 += sum[i] * x->sz - x->sum;
      }
      trans(y, extra, q, i);
      b = treap::merge(x, y);
      slot -= need;
    }
    treap::rt = treap::merge(treap::merge(a, b), c);
    treap::add(i, sum[i]);
  }
  if (extra.size() < q) {
    treap::init();
    slot = m - qq;
    for (int i = n - 1; i >= 0; --i) {
      treap::node *a = 0, *b = 0, *c = 0, *d = 0;
      std::tie(d, c) = treap::split(treap::rt, sum[i] - sum1);
      std::tie(b, c) = treap::split(c, sum[i] - sum2);
      std::tie(a, b) = treap::split(b, sum[i] - sum2 - 1);
      if (a) trans(a, extra, q, i);
      if (b) {
        int need = std::min<ll>(slot, b->sz);
        treap::node *x, *y;
        std::tie(x, y) = split_by_size(b, need);
        if (x) trans(x, extra, q, i);
        b = treap::merge(x, y);
        slot -= need;
      }
      treap::rt = treap::merge(treap::merge(d, a), treap::merge(b, c));
      treap::add(i, sum[i]);
    }
  }
  std::sort(extra.begin(), extra.end(), [&](const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return sum[a.first] - sum[a.second + 1] > sum[b.first] - sum[b.second + 1];
  });
  std::vector<int> mark(n + 1, 0);
  std::set<int> uncovered;
  kth::init(q - 1);
  int last = -1;
  for (int i = 0; i < n; ++i) {
    if (cov[i] != -1) mark[i]++, mark[cov[i]]--;
    if (i) mark[i] += mark[i - 1];
    if (!mark[i]) {
      if (last != -1) kth::add(get(last, i));
      uncovered.insert(i);
      last = i;
    }
  }
  ll ret = -inf;
  for (int i = 0; i <= q; ++i) {
    int rest = q - i;
    if (rest <= uncovered.size()) {
      ll ans2 = 0;
      if (uncovered.size() && rest) {
        int x = *uncovered.begin();
        int y = *uncovered.rbegin();
        ans2 = max_sum[x] - min_sum[y + 1];
      }
      if (rest || uncovered.empty()) {
        ret = std::max(ret, ans1 + ans2 - kth::sum);
      }
    }
    if (i == q) break;
    int l = extra[i].first, r = extra[i].second;
    int x = -1, y = -1;
    ans1 += sum[l] - sum[r + 1];
    std::vector<int> rm;
    auto it = uncovered.lower_bound(l);
    if (it != uncovered.begin()) --it, x = *it, ++it;
    for (; it != uncovered.end() && *it <= r; ) {
      rm.push_back(*it);
      it = uncovered.erase(it);
    }
    if (it != uncovered.end()) y = *it;
    if (rm.size()) {
      if (x != -1) kth::del(get(x, rm[0]));
      if (y != -1) kth::del(get(rm.back(), y));
      for (size_t j = 1; j < rm.size(); ++j) {
        kth::del(get(rm[j - 1], rm[j]));
      }
    }
    if (x != -1 && y != -1 && !rm.empty()) kth::add(get(x, y));
    kth::reduce();
  }
  printf("%lld\n", ret);
  return 0;
}
