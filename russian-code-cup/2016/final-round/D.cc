#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

const int N = 1000000 + 10, mod = 1e9 + 7;

struct node {
  int sum, zero;
  void mark() {
    zero = true;
    sum = 0;
  }
} T[N << 2];

void update(int rt) {
  T[rt].sum = (T[rt << 1].sum + T[rt << 1 | 1].sum) % mod;
}

void pushdown(int rt) {
  if (T[rt].zero) {
    T[rt << 1].mark();
    T[rt << 1 | 1].mark();
    T[rt].zero = 0;
  }
}

void build(int rt, int l, int r) {
  T[rt].zero = T[rt].sum = 0;
  if (l + 1 == r) return;
  int m = (l + r) >> 1;
  build(rt << 1, l, m);
  build(rt << 1 | 1, m, r);
}

void set(int rt, int l, int r, int x, int v) {
  if (l + 1 == r) {
    T[rt].sum = v;
    return;
  }
  pushdown(rt);
  int m = (l + r) >> 1;
  if (x < m) set(rt << 1, l, m, x, v);
  else set(rt << 1 | 1, m, r, x, v);
  update(rt);
}

int sum(int rt, int l, int r, int L, int R) {
  if (L <= l && R >= r) return T[rt].sum;
  pushdown(rt);
  int ret = 0, m = (l + r) >> 1;
  if (L < m) ret += sum(rt << 1, l, m, L, R);
  if (R > m) ret += sum(rt << 1 | 1, m, r, L, R);
  return ret % mod;
}

void clear(int rt, int l, int r, int L, int R) {
  if (L <= l && R >= r) {
    T[rt].mark();
    return;
  }
  pushdown(rt);
  int m = (l + r) >> 1;
  if (L < m) clear(rt << 1, l, m, L, R);
  if (R > m) clear(rt << 1 | 1, m, r, L, R);
  update(rt);
}

std::vector<std::pair<int, int>> ins[N], del[N];

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < k; ++i) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    --x1, --y1, --y2;
    ins[x1].emplace_back(y1, y2);
    del[x2].emplace_back(y1, y2);
  }
  std::multiset<int> obs;
  auto find = [&obs](int x) {
    auto it = obs.upper_bound(x);
    if (it == obs.begin()) return 0;
    else return *(--it) + 1;
  };
  build(1, 0, m);
  set(1, 0, m, 0, 1);
  for (auto &&e: ins[0]) {
    obs.insert(e.first);
    obs.insert(e.second);
  }
  for (int i = 1; i < n; ++i) {
    std::vector<int> add;
    for (auto &&e: ins[i]) {
      int r = e.second + 1;
      int l = find(r);
      add.push_back(l <= r && r < m ? sum(1, 0, m, l, r + 1) : 0);
    }
    std::reverse(add.begin(), add.end());
    for (auto &&e: ins[i]) {
      if (e.second + 1 < m) {
        set(1, 0, m, e.second + 1, add.back());
      }
      add.pop_back();
    }
    for (auto &&e: ins[i]) {
      clear(1, 0, m, e.first, e.second + 1);
      obs.insert(e.first);
      obs.insert(e.second);
    }
    for (auto &&e: del[i]) {
      obs.erase(obs.find(e.first));
      obs.erase(obs.find(e.second));
    }
  }
  int l = find(m - 1);
  printf("%d\n", sum(1, 0, m, l, m));
  return 0;
}
