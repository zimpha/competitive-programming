#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using i64 = long long;
using i128 = __int128_t;

const int N = 1e5 + 10;

struct Point {
  i64 x, y, w;
  bool operator < (const Point &rhs) const {
    return x * rhs.y - y * rhs.x > 0;
  }
  Point operator - (const Point &rhs) const {
    return {x - rhs.x, y - rhs.y, 0};
  }
  i64 det(const Point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  i64 dot(const Point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  i64 norm() const {
    return x * x + y * y;
  }
} p[N];

struct Event {
  i64 x, y;
  int i, j;
};

int order[N], pos[N];
int sum[N], bound;
Event events[N * 10];

void add(int x, int v) {
  for (; x >= 0; x -= ~x & x + 1) {
    sum[x] += v;
  }
}

int get(int x, int r = 0) {
  for (; x < bound; x += ~x & x + 1) {
    r += sum[x];
  }
  return r;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld%lld", &p[i].x, &p[i].y, &p[i].w);
  }
  int size = sqrt(n);
  i64 ret = 0;
  for (int l = 0; l < n; l += size) {
    int r = std::min(l + size, n);
    for (int i = l; i < r; ++i) {
      order[i] = i;
      for (int j = i + 1; j < r; ++j) {
        if (p[i].dot(p[j]) >= k) ret += p[i].w * p[j].w;
      }
    }
    std::sort(p, p + l);
    std::sort(p + l, p + r);
    if (!l) continue;
    int en = 0;
    for (int i = l; i < r; ++i) {
      for (int j = i + 1; j < r; ++j) {
        if (p[i].det(p[j]) == 0) continue;
        int a = i, b = j;
        auto ab = p[b] - p[a];
        i64 norm = ab.norm();
        i64 scale = ab.dot(p[a]);
        i64 ox = p[a].x * norm - ab.x * scale;
        i64 oy = p[a].y * norm - ab.y * scale;
        if (oy > 0 && ox >= 0) {
          if ((ox + 1) * p[a].x + oy * p[a].y > (ox + 1) * p[b].x + oy * p[b].y) {
            std::swap(a, b);
          }
          events[en++] = (Event){ox, oy, a, b};
        }
      }
    }

    std::sort(events, events + en, [&](const Event &a, const Event &b) {
      i128 side = (i128)a.x * b.y - (i128)a.y * b.x;
      if (side != 0) return side > 0;
      if ((p[a.j] - p[a.i]).det(p[b.j] - p[b.i]) == 0) {
        return a.i == b.i ? a.j > b.j : a.i > b.i;
      } else {
        return a.i < b.i;
      }
    });

    // start from vector (1, 0)
    std::sort(order + l, order + r, [&](int i, int j) {
      return p[i].x == p[j].x ? p[i].y < p[j].y : p[i].x < p[j].x;
    });
    bound = r - l;
    memset(sum, 0, sizeof(*sum) * bound);
    for (int i = l; i < r; ++i) {
      add(i - l, p[order[i]].w);
      pos[order[i]] = i;
    }

    for (int i = 0, j = 0; i < l; ++i) {
      for (; j < en && p[i].x * events[j].y - p[i].y * events[j].x <= 0; ++j) {
        int a = events[j].i, b = events[j].j;
        int pa = pos[a], pb = pos[b];
        assert(pa < pb);
        if (pa + 1 != pb) continue;
        order[pa] = b;
        order[pb] = a;
        pos[order[pa]] = pa;
        pos[order[pb]] = pb;
        add(pa - l, -p[a].w + p[b].w);
        add(pb - l, -p[b].w + p[a].w);
      }
      // now we can query
      int left = l, right = r - 1;
      while (left < right) {
        int mid = (left + right - 1) >> 1;
        if (p[i].dot(p[order[mid]]) >= k) right = mid;
        else left = mid + 1;
      }
      if (p[i].dot(p[order[left]]) < k) ++left;
      ret += (i64)p[i].w * get(left - l);
    }
  }
  printf("%lld\n", ret);
  return 0;
}
