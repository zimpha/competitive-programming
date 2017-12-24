#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

using flt = double;
const flt eps = 1e-12, inf = 1e30, PI = acos(-1.0);
template<typename T>
inline T sqr(T x) {return x * x;}
inline flt cmp(flt a, flt b, flt e = eps) {
  return fabs(a - b) >= e + fabs(a) * e ? a - b : 0;
}
inline int sgn(flt x, flt e = eps) {return x < -e ? -1 : (x > e);}
inline flt fix(flt x, flt e = eps) {return cmp(x, 0, e);}

struct point {
  flt x, y;
  point(flt x = 0, flt y = 0): x(x), y(y) {}
  bool operator < (const point &rhs) const {
    return cmp(x, rhs.x) < 0 || (cmp(x, rhs.x) == 0 && cmp(y, rhs.y) < 0);
  }
  bool operator == (const point &rhs) const {
    return cmp(x, rhs.x) == 0 && cmp(y, rhs.y) == 0;
  }
  point operator + (const point &rhs) const {
    return point(x + rhs.x, y + rhs.y);
  }
  point operator - (const point &rhs) const {
    return point(x - rhs.x, y - rhs.y);
  }
  point operator * (const flt k) const {
    return point(x * k, y * k);
  }
  point operator / (const flt k) const {
    return point(x / k, y / k);
  }
  point operator ~ () const {// counter clockwise rotate 90 degree
    return point(-y, x);
  }
  flt dot(const point &rhs) const {
    return x * rhs.x + y * rhs.y;
  }
  flt det(const point &rhs) const {
    return x * rhs.y - y * rhs.x;
  }
  flt norm2() const {
    return x * x + y * y;
  }
  flt norm() const {
    return hypot(x, y);
  }
  point rot(flt a) const {// counter clockwise rotate A rad
    return point(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  point rot(flt cosa, flt sina) const {// counter clockwise rotate using cos/sin
    return point(x * cosa - y * sina, x * sina + y * cosa);
  }
  point trunc(flt a = 1.0) const {
    return (*this) * (a / this->norm());
  }
};

using poly_t = std::vector<point>;

// intersection of half plane
struct halfplane_t {
  point a, b; // left side of vector \vec{ab}, i.e. \vec{ab} \times \vec{ap} > 0
  flt ang;
  halfplane_t() {}
  halfplane_t(const point &a, const point &b): a(a), b(b) {
    ang = atan2(b.y - a.y, b.x - a.x);
  }
  bool operator < (const halfplane_t &l) const {
    int res = sgn(ang - l.ang);
    return res == 0 ? l.side(a) > 0 : res < 0;
  }
  int side(const point &p) const {// 1: left, 0: on, -1:right
    return sgn((b - a).det(p - a));
  }
  point inter(const halfplane_t &l) const {
    flt k = (l.a - l.b).det(a - l.b);
    k = k / (k - (l.a - l.b).det(b - l.b));
    return a + (b - a) * k;
  }
};

poly_t half_plane(std::vector<halfplane_t> v) {
  std::sort(v.begin(), v.end());
  std::deque<halfplane_t> q;
  q.push_back(v[0]);
  std::deque<point> ans;
  for (size_t i = 1; i < v.size(); ++ i) {
    if (sgn(v[i].ang - v[i - 1].ang) == 0) continue;
    while (ans.size() && v[i].side(ans.back()) < 0) ans.pop_back(), q.pop_back();
    while (ans.size() && v[i].side(ans.front()) < 0) ans.pop_front(), q.pop_front();
    ans.push_back(q.back().inter(v[i]));
    q.push_back(v[i]);
  }
  while (ans.size() && q.front().side(ans.back()) < 0) ans.pop_back(), q.pop_back();
  while (ans.size() && q.back().side(ans.front()) < 0) ans.pop_front(), q.pop_front();
  if (q.size() <= 2) return poly_t();
  std::vector<point> pt(ans.begin(), ans.end());
  pt.push_back(q.front().inter(q.back()));
  std::sort(pt.begin(), pt.end());
  pt.erase(std::unique(pt.begin(), pt.end()), pt.end());
  return pt;
}

bool good(const poly_t &a, const poly_t &b) {
  std::vector<halfplane_t> half;
  for (int i = 0, n = a.size(); i < n; ++i) {
    half.emplace_back(a[i], a[(i + 1) % n]);
  }
  for (int i = 0, n = b.size(); i < n; ++i) {
    half.emplace_back(b[i], b[(i + 1) % n]);
  }
  return half_plane(half).size() > 2;
}

bool good(const poly_t &a, const poly_t &b, const poly_t &c) {
  std::vector<halfplane_t> half;
  for (int i = 0, n = a.size(); i < n; ++i) {
    half.emplace_back(a[i], a[(i + 1) % n]);
  }
  for (int i = 0, n = b.size(); i < n; ++i) {
    half.emplace_back(b[i], b[(i + 1) % n]);
  }
  for (int i = 0, n = c.size(); i < n; ++i) {
    half.emplace_back(c[i], c[(i + 1) % n]);
  }
  auto r = half_plane(half);
  return r.size() > 2;
}

const int N = 30, S = 1 << 20;

poly_t poly[N];
std::vector<int> maximal[N];
int popcount[S], valid[S], dp[S];

int main() {
  for (int i = 1; i < S; ++i) {
    popcount[i] = popcount[i >> 1] + (i & 1);
  }
  for (int n; scanf("%d", &n) == 1 && n; ) {
    for (int i = 0; i < n; ++i) {
      int m;
      scanf("%d", &m);
      poly[i].resize(m);
      for (int j = 0; j < m; ++j) {
        scanf("%lf%lf", &poly[i][j].x, &poly[i][j].y);
      }
      double sum = 0;
      for (int j = 0; j < m; ++j) {
        sum += poly[i][j].det(poly[i][(j + 1) % m]);
      }
      if (sum < 0) {
        std::reverse(poly[i].begin(), poly[i].end());
      }
    }
    int s = 1 << n;
    memset(valid, 0, sizeof(*valid) * s);
    for (int i = 0; i < n; ++i) {
      valid[1 << i] = 1;
      for (int j = 0; j < i; ++j) {
        if (good(poly[i], poly[j])) {
          valid[(1 << i) | (1 << j)] = 1;
          for (int k = 0; k < j; ++k) {
            valid[(1 << i) | (1 << j) | (1 << k)] = good(poly[i], poly[j], poly[k]);
          }
        }
      }
    }
    for (int mask = 1; mask < s; ++mask) {
      if (popcount[mask] < 3 && valid[mask]) continue;
      static int bs[N], m;
      for (int i = 0; i < n; ++i) if (~mask >> i & 1) {
        bool flag = true;
        m = 0;
        for (int a = 0; a < n && flag; ++a) if (mask >> a & 1) {
          bs[m++] = a;
          for (int j = 0; j < m; ++j) {
            int b = bs[j];
            if (!valid[(1 << i) | (1 << a) | (1 << b)]) {
              flag = false;
              break;
            }
          }
        }
        valid[mask | (1 << i)] |= flag;
      }
    }
    for (int i = 0; i < n; ++i) maximal[i].clear();
    for (int mask = 1; mask < s; ++mask) if (valid[mask]) {
      bool flag = true;
      for (int i = 0; i < n && flag; ++i) if (~mask >> i & 1) {
        if (valid[mask | (1 << i)]) flag = false;
      }
      if (flag) {
        for (int i = 0; i < n; ++i) {
          if (mask >> i & 1) {
            maximal[i].emplace_back(mask);
          }
        }
      }
    }
    memset(dp, -1, sizeof(*dp) * s);
    dp[0] = 0;
    for (int mask = 0; mask < s; ++mask) if (dp[mask] != -1) {
      int r = 0;
      for (; r < n && (mask >> r & 1); ++r);
      if (r == n) break;
      for (auto &&add: maximal[r]) {
        if (dp[add | mask] == -1 || dp[add | mask] > dp[mask] + 1) {
          dp[add | mask] = dp[mask] + 1;
        }
      }
    }
    printf("%d\n", dp[s - 1]);
  }
  return 0;
}
