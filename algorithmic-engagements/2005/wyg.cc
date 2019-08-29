#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>

using int64 = long long;
using pii = std::pair<int, int>;

struct line {
  int p, l, r;
  bool operator < (const line& rhs) const {
    return p < rhs.p;
  }
};

const int N = 1e5 + 10;

pii go[N][4];

int main() {
  int s, k;
  int64 t;
  scanf("%d%d%lld", &s, &k, &t);
  std::vector<pii> ps;
  std::vector<line> ver, hor;
  int sx, sy;
  for (int i = 0; i < s; ++i) {
    int x1, x2, y1, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    if (i == 0) sx = (x1 + x2) / 2, sy = (y1 + y2) / 2;
    if (x1 == x2) {
      ver.emplace_back();
      ver.back().p = x1;
      ver.back().l = std::min(y1, y2);
      ver.back().r = std::max(y1, y2);
    } else {
      hor.emplace_back();
      hor.back().p = y1;
      hor.back().l = std::min(x1, x2);
      hor.back().r = std::max(x1, x2);
    }
  }
  for (auto &e: ver) {
    for (int i = e.l; i <= e.r; ++i) {
      ps.emplace_back(e.p, i);
    }
  }
  for (auto &e: hor) {
    for (int i = e.l; i <= e.r; ++i) {
      ps.emplace_back(i, e.p);
    }
  }
  std::sort(ps.begin(), ps.end());
  ps.erase(std::unique(ps.begin(), ps.end()), ps.end());
  return 0;
}
