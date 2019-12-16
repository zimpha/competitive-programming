#include <cstdio>
#include <random>
#include <cstring>
#include <cassert>
#include <set>
#include <algorithm>

using int64 = long long;

const int N = 1e5 + 10;

struct SegmentTree {
  int u[N], n;
  void init(int _n) {
    n = _n;
    memset(u, 0, sizeof(*u) * n);
  }
  void add_low(int x, int v) {
    for (; x >= 0; x -= ~x & x + 1) {
      u[x] = std::max(u[x], v);
    }
  }
  int get_low(int x, int r = 0) {
    for (; x < n; x += ~x & x + 1) {
      r = std::max(r, u[x]);
    }
    return r;
  }
  void add_upp(int x, int v) {
    for (; x < n; x += ~x & x + 1) {
      u[x] = std::max(u[x], v);
    }
  }
  int get_upp(int x, int r = 0) {
    for (; x >= 0; x -= ~x & x + 1) {
      r = std::max(r, u[x]);
    }
    return r;
  }
} low, upp;

std::set<int> row[N], col[N];
int64 queue[N * 20];
int n, m, k;

int main() {
  scanf("%d%d%d", &n, &m, &k);
  low.init(m);
  upp.init(m);
  for (int i = 0; i < n; ++i) row[i].clear();
  for (int i = 0; i < m; ++i) col[i].clear();
  int x = 0;
  for (int i = 0; i < k; ++i) {
    int r, c, z;
    scanf("%d%d%d", &r, &c, &z);
    r = (r ^ x) % n;
    c = (c ^ x) % m;
    int h_low = n - 1 - r, h_upp = r;
    bool touch_low = false, touch_upp = false;
    int lc = low.get_low(c), uc = upp.get_upp(c);
    if (lc == h_low) touch_low = true;
    else if (lc > h_low) touch_low = false;
    else if (c == 0 || low.get_low(c - 1) >= h_low) touch_low = true;
    if (uc == h_upp) touch_upp = true;
    else if (uc > h_upp) touch_upp = false;
    else if (c == m - 1 || upp.get_upp(c + 1) >= h_upp) touch_upp = true;
    if (lc <= h_low && uc <= h_upp) {
      if (lc + uc + 1 >= n) touch_low = touch_upp = 1;
    }
    if (touch_low && touch_upp) puts("TAK"), x ^= z;
    else {
      puts("NIE");
      if (!touch_low && !touch_upp) {
        row[r].insert(c);
        col[c].insert(r);
        continue;
      }
      int head = 0, tail = 0;
      queue[tail++] = (int64)r * m + c;
      for (; head < tail; ++head) {
        r = queue[head] / m, c = queue[head] % m;
        if (touch_low) {
          int h = low.get_low(c);
          if (h >= n - r) continue;
          low.add_low(c, n - r);
          auto &s = row[r - 1];
          for (auto it = s.begin(); it != s.end(); ) {
            if (*it > c + 1) break;
            queue[tail++] = (int64)(r - 1) * m + *it;
            col[*it].erase(r - 1);
            it = s.erase(it);
          }
          auto &t = col[c + 1];
          auto it = t.lower_bound(r - 1);
          for (; it != t.end(); ) {
            queue[tail++] = (int64)*it * m + c + 1;
            row[*it].erase(c + 1);
            it = t.erase(it);
          }
        } else {
          int h = upp.get_upp(c);
          if (h >= r + 1) continue;
          upp.add_upp(c, r + 1);
          auto &s = col[c - 1];
          for (auto it = s.begin(); it != s.end(); ) {
            if (*it > r + 1) break;
            queue[tail++] = (int64)*it * m + c - 1;
            row[*it].erase(c - 1);
            it = s.erase(it);
          }
          auto &t = row[r + 1];
          auto it = t.lower_bound(c - 1);
          for (; it != t.end(); ) {
            queue[tail++] = (int64)(r + 1) * m + *it;
            col[*it].erase(r + 1);
            it = t.erase(it);
          }
        }
      }
    }
  }
  return 0;
}
