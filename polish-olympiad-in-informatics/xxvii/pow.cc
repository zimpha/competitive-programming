#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

const int N = 250000 + 10, M = N * 40;

int ls[M], rs[M], val[M], sz;

void init() {
  ls[0] = rs[0] = 0;
  val[0] = 0;
  sz = 1;
}

int new_node() {
  ls[sz] = rs[sz] = val[sz] = 0;
  return sz++;
}

int ins(int o, int l, int r, int x, int v) {
  int p = new_node();
  ls[p] = ls[o]; rs[p] = rs[o]; val[p] = val[o] + v;
  if (l + 1 == r) return p;
  int m = (l + r) >> 1;
  if (x < m) ls[p] = ins(ls[o], l, m, x, v);
  else rs[p] = ins(rs[o], m, r, x, v);
  return p;
}

int query(int o, int l, int r, int L, int R) {
  if (L <= l && r <= R) return val[o];
  int m = (l + r) >> 1, ret = 0;
  if (L < m) ret += query(ls[o], l, m, L, R);
  if (R > m) ret += query(rs[o], m, r, L, R);
  return ret;
}

std::vector<std::pair<int, int>> queue[N];
int next[N], prev[N], root[N];
int xs[N], n, m;

void inicjuj(int _n, std::vector<int> t) {
  n = _n;
  for (int i = 0; i < n; ++i) xs[i] = t[i];
  std::sort(xs, xs + n);
  m = std::unique(xs, xs + n) - xs;
  for (int i = 0; i < n; ++i) {
    t[i] = std::lower_bound(xs, xs + m, t[i]) - xs;
  }

  for (int i = 0; i < n; ++i) {
    if (!i || t[i] != t[i - 1]) prev[i] = 1;
    else prev[i] = prev[i - 1] + 1;
  }
  for (int i = n - 1; i >= 0; --i) {
    if (i == n - 1 || t[i] != t[i + 1]) next[i] = 1;
    else next[i] = next[i + 1] + 1;
  }

  queue[t[0]].emplace_back(0, 1);
  init();
  for (int i = 1; i < n; ++i) {
    auto &qs = queue[t[i]];
    root[i] = root[i - 1];
    if (prev[i] != 1) {
      while (!qs.empty() && qs.back().second < prev[i]) {
        qs.pop_back();
      }
      int p = qs.empty() ? 0 : qs.back().first + 1;
      root[i] = ins(root[i], 0, n, p, 1);
      root[i] = ins(root[i], 0, n, i, -1);
    }
    if (i == n - 1 || t[i] != t[i + 1]) {
      for (int j = i - prev[i] + 1; j <= i; ++j) {
        while (!qs.empty() && qs.back().second <= next[j]) {
          qs.pop_back();
        }
        qs.emplace_back(j, next[j]);
      }
    } else {
      qs.emplace_back(i - prev[i] + 1, prev[i]);
    }
  }
}

int ile_powtorzen(int a, int b) {
  return query(root[b], 0, n, 0, a + 1);
}
