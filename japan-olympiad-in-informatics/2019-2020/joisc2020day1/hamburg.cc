#include <cstdio>
#include <algorithm>

const int N = 2e5 + 10;
const int inf = 1e9;

using int64 = long long;

struct Rect {
  int l, r;
  int d, u;

  Rect inter(const Rect &o) const {
    Rect ret;
    ret.l = std::max(l, o.l);
    ret.r = std::min(r, o.r);
    ret.d = std::max(d, o.d);
    ret.u = std::min(u, o.u);
    return ret;
  }
  double cnt() const {
    if (l > r || d > u) return 0;
    return 1.0 * (r - l + 1) * (u - d + 1);
  }
};

Rect a[5][N];
std::pair<int, int> ret[5];
int n, k;

int eliminate(Rect *a, Rect *b, int dn, int x, int y) {
  int nn = 0;
  for (int i = 0; i < dn; ++i) {
    if (a[i].l <= x && x <= a[i].r && a[i].d <= y && y <= a[i].u) continue;
    b[nn++] = a[i];
  }
  return nn;
}

bool dfs(int dn, int dk) {
  int l = 0, r = inf, d = 0, u = inf, nn;
  for (int i = 0; i < dn; ++i) {
    l = std::max(l, a[dk][i].l);
    r = std::min(r, a[dk][i].r);
    d = std::max(d, a[dk][i].d);
    u = std::min(u, a[dk][i].u);
  }
  if (l <= r && d <= u) {
    for (int i = 1; i < dk; ++i) puts("1 1");
    ret[dk] = {l, d};
    for (int i = dk; i <= k; ++i) {
      printf("%d %d\n", ret[i].first, ret[i].second);
    }
    return true;
  }
  if (dk == 1) return false;
  nn = eliminate(a[dk], a[dk - 1], dn, l, d);
  ret[dk] = {l, d};
  if (dfs(nn, dk - 1)) return true;
  nn = eliminate(a[dk], a[dk - 1], dn, l, u);
  ret[dk] = {l, u};
  if (dfs(nn, dk - 1)) return true;
  nn = eliminate(a[dk], a[dk - 1], dn, r, d);
  ret[dk] = {r, d};
  if (dfs(nn, dk - 1)) return true;
  nn = eliminate(a[dk], a[dk - 1], dn, r, u);
  ret[dk] = {r, u};
  if (dfs(nn, dk - 1)) return true;
  return false;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d%d", &a[k][i].l, &a[k][i].d, &a[k][i].r, &a[k][i].u);
  }
  if (dfs(n, k)) return 0;
  while (true) {
    std::random_shuffle(a[k], a[k] + n);
    Rect ret[k];
    for (int i = 0; i < k; ++i) ret[i] = a[k][i];
    bool found = false;
    for (int i = k; i < n && !found; ++i) {
      double best = inf;
      int choose = -1;
      for (int j = 0; j < k; ++j) {
        auto t = ret[j].inter(a[k][i]);
        double ratio = (ret[j].cnt() - t.cnt()) / ret[j].cnt();
        if (choose == -1 || ratio < best) {
          best = ratio;
          choose = j;
        }
      }
      ret[choose] = ret[choose].inter(a[k][i]);
      if (ret[choose].cnt() == 0) found = true;
    }
    if (!found) {
      for (int i = 0; i < k; ++i) printf("%d %d\n", ret[i].l, ret[i].d);
      break;
    }
  }
  return 0;
}
