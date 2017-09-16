#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

inline int sgn(int64 x) {return x < 0 ? -1 : x > 0;}

struct point {
  int64 x, y;
  point(int64 a = 0, int64 b = 0): x(a), y(b) {}
  bool operator < (const point &rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }
  bool operator == (const point &rhs) const {
    return x == rhs.x && y == rhs.y;
  }
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  point operator * (const int64 k) const {
    return point(x * k, y * k);
  }
  int64 det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  int64 dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
};

using poly_t = std::vector<point>;
using factory_t = std::pair<point, int>;
using query_t = std::pair<point, int>;

poly_t convex_hull(poly_t u) {
  std::sort(u.begin(), u.end());
  u.erase(std::unique(u.begin(), u.end()), u.end());
  if (u.size() < 3u) return u;
  poly_t ps;
  for (size_t i = 0, o = 1, m = 1; ~i; i += o) {
    while (ps.size() > m) {
      point A = ps.back() - ps[ps.size() - 2];
      point B = ps.back() - u[i];
      if (sgn(A.det(B)) < 0) break;
      ps.pop_back();
    }
    ps.push_back(u[i]);
    if (i + 1 == u.size()) m = ps.size(), o = -1;
  }
  ps.pop_back();
  return std::move(ps);
}

struct event_t {
  point a, b;
  int type;
};

void solve(
  const point &a, const point &b, 
  const std::vector<query_t> &q, 
  const std::vector<factory_t> &f, 
  std::vector<int64> &ret) {
  std::vector<event_t> ev(q.size() + f.size());
  std::vector<int64> xs;
  for (size_t i = 0; i < q.size(); ++i) {
    ev[i].a = a * q[i].second + q[i].first;
    ev[i].b = b * q[i].second + q[i].first;
    if (a.x == b.x) {
      xs.push_back(ev[i].a.y);
      xs.push_back(ev[i].b.y);
    } else {
      xs.push_back(ev[i].a.x);
      xs.push_back(ev[i].b.x);
    }
    ev[i].type = -i;
  }
  for (size_t i = 0; i < f.size(); ++i) {
    ev[i + q.size()].a = f[i].first;
    ev[i + q.size()].type = f[i].second;
    if (a.x == b.x) {
      xs.push_back(f[i].first.y);
    } else {
      xs.push_back(f[i].first.x);
    }
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  auto get_id = [&xs] (int64 v) {
    return std::lower_bound(xs.begin(), xs.end(), v) - xs.begin();
  };
  auto add = [] (std::vector<int64> &bit, int x, int64 v) {
    for (; x < bit.size(); x += ~x & x + 1) bit[x] += v;
  };
  auto sum = [] (std::vector<int64> &bit, int x, int64 r = 0) {
    for (; x >= 0; x -= ~x & x + 1) r += bit[x];
    return r;
  };
  if (a.x == b.x) {
    std::vector<int64> bit(xs.size());
    std::sort(ev.begin(), ev.end(), [](const event_t &u, const event_t &v){
      if (u.a.x != v.a.x) return u.a.x < v.a.x;
      else return u.type > v.type;
    });
    for (int i = 0, j, n = ev.size(); i < n; ) {
      for (j = i; j < n && ev[i].a.x == ev[j].a.x; ++j) {
        ev[j].a.y = get_id(ev[j].a.y);
        if (ev[j].type <= 0) {
          ev[j].b.y = get_id(ev[j].b.y);
          if (ev[j].a.y < ev[j].b.y) ret[-ev[j].type] -= sum(bit, ev[j].a.y - 1);
          else ret[-ev[j].type] += sum(bit, ev[j].a.y);
        } else {
          add(bit, ev[j].a.y, ev[j].type);
        }
      }
      for (; i < j; ++i) if (ev[i].type > 0) {
        add(bit, ev[i].a.y, -ev[i].type);
      }
    }
  } else {
    point dir = b - a;
    std::sort(ev.begin(), ev.end(), [&dir](const event_t &u, const event_t &v) {
      if (dir.det(u.a - v.a) != 0) {
        return dir.x > 0 ? dir.det(u.a - v.a) < 0 : dir.det(u.a - v.a) > 0;
      } else {
        return u.type > v.type;
      }
    });
    std::vector<int64> bit_on(xs.size()), bit_below(xs.size());
    for (int i = 0, j, n = ev.size(); i < n; ) {
      point o = ev[i].a;
      for (j = i; j < n && dir.det(ev[j].a - o) == 0; ++j) {
        ev[j].a.x = get_id(ev[j].a.x);
        if (ev[j].type <= 0) {
          ev[j].b.x = get_id(ev[j].b.x);
          int l = ev[j].a.x, r = ev[j].b.x;
          if (l < r) ret[-ev[j].type] -= sum(bit_below, r - 1) - sum(bit_below, l - 1);
          else {
            ret[-ev[j].type] += sum(bit_below, l) - sum(bit_below, r);
            ret[-ev[j].type] += sum(bit_on, l) - sum(bit_on, r);
          }
        } else {
          add(bit_on, ev[j].a.x, ev[j].type);
        }
      }
      for (; i < j; ++i) if (ev[i].type > 0) {
        add(bit_on, ev[i].a.x, -ev[i].type);
        add(bit_below, ev[i].a.x, ev[i].type);
      }
    }
  }
}

int main() {
  int n, q, k;
  scanf("%d%d%d", &k, &n, &q);
  std::vector<point> v(k);
  for (int i = 0; i < k; ++i) {
    scanf("%lld%lld", &v[i].x, &v[i].y);
  }
  std::vector<point> hull;
  for (int mask = 0; mask < (1 << k); ++mask) {
    point o(0, 0);
    for (int i = 0; i < k; ++i) {
      if (mask >> i & 1) o = o + v[i];
      else o = o - v[i];
    }
    hull.push_back(o);
  }
  hull = convex_hull(hull);
  std::vector<factory_t> factory(n);
  std::vector<query_t> query(q);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld%d", &factory[i].first.x, &factory[i].first.y, &factory[i].second);
  }
  for (int i = 0; i < q; ++i) {
    scanf("%lld%lld%d", &query[i].first.x, &query[i].first.y, &query[i].second);
  }
  std::vector<int64> ret(q);
  bool found = false;
  for (size_t i = 0; i < hull.size(); ++i) {
    const point &a = hull[i], &b = hull[(i + 1) % hull.size()];
    if (a.x == b.x) found = true;
    solve(a, b, query, factory, ret);
  }
  if (!found) {
    point a = hull[0], b = hull[0];
    for (size_t i = 0; i < hull.size(); ++i) {
      if (hull[i].x < a.x) a = hull[i];
      if (hull[i].x > b.x) b = hull[i];
    }
    solve(a, {a.x, a.y - 1}, query, factory, ret);
    solve(b, {b.x, b.y + 1}, query, factory, ret);
  }
  for (int i = 0; i < q; ++i) {
    printf("%lld\n", ret[i]);
  }
  return 0;
}