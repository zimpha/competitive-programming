#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using int64 = long long;
using int128 = __int128;

int64 gcd(int64 x, int64 y) {
  return y ? gcd(y, x % y) : x;
}

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
  int128 det(const point &rhs) const {
    return (int128)x * rhs.y - (int128)y * rhs.x;
  }
  int128 norm2() const {
    return (int128)x * x + (int128)y * y;
  }
  void reduce() {
    if (y < 0 || (y == 0 && x < 0)) x = -x, y = -y;
    int64 g = gcd(std::abs(x), std::abs(y)); 
    x /= g, y /= g;
  }
};

std::vector<point> convex(const std::vector<point> &u) {
  if (u.size() < 3u) return u;
  std::vector<point> v;
  for (size_t i = 0, o = 1, m = 1; ~i; i += o) {
    while (v.size() > m) {
      point A = v.back() - v[v.size() - 2];
      point B = v.back() - u[i];
      if (A.det(B) < 0) break;
      v.pop_back();
    }
    v.push_back(u[i]);
    if (i + 1 == u.size()) m = v.size(), o = -1;
  }
  v.pop_back();
  return v;
}

std::vector<int> manacher(const std::vector<int128> &s, int n) {
  std::vector<int> u(n <<= 1, 0);
  for (int i = 0, j = 0, k; i < n; i += k, j = std::max(j - k, 0)) {
    while (i >= j && i + j + 1 < n && s[(i - j) >> 1] == s[(i + j + 1) >> 1]) ++j;
    for (u[i] = j, k = 1; i >= k && u[i] >= k && u[i - k] != u[i] - k; ++k) {
      u[i + k] = std::min(u[i - k], u[i] - k);
    }
  }
  return u;
}

int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::pair<int128, point>> p(n);
  point center{0, 0};
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &p[i].second.x, &p[i].second.y);
    center = center + p[i].second;
    p[i].second.x *= n;
    p[i].second.y *= n;
  }
  for (int i = 0; i < n; ++i) {
    p[i].second = p[i].second - center;
    p[i].first = p[i].second.norm2();
  }
  std::sort(p.begin(), p.end());
  std::map<point, int> axis;
  int layers = 0;
  for (int i = 0, j; i < n; i = j, ++layers) {
    std::vector<point> hull;
    for (j = i; j < n && p[i].first == p[j].first; ++j) {
      hull.push_back(p[j].second);
    }
    hull = convex(hull);
    int m = hull.size();
    if (m == 1) {
      if (hull[0].x == 0 && hull[0].y == 0) layers--;
      else {
        hull[0].reduce();
        axis[hull[0]] += 1;
      }
    } else if (m == 2) {
      point a = hull[0] + hull[1];
      if (a.x == 0 && a.y == 0) {
        a = {-hull[0].y, hull[0].x};
        hull[0].reduce();
        axis[hull[0]]++;
      }
      a.reduce();
      axis[a]++;
    } else {
      std::vector<point> all;
      std::vector<int128> s(m * 2);
      for (int i = 0; i < m * 2; ++i) {
        s[i] = (hull[i % m] - hull[(i + 1) % m]).norm2();
      }
      auto u = manacher(s, m * 2);
      for (int i = 0; i < m; ++i) {
        // symmetry axis pass the point
        if (u[i + m + i - 1] >= m) {
          all.push_back(hull[i]);
          all.back().reduce();
        }
        // symmetry axis pass the edge
        if (u[i + m + i] >= m - 1) {
          all.push_back(hull[i] + hull[(i + 1) % m]);
          if (all.back().x == 0 && all.back().y == 0) {
            all.back() = {-hull[i].y, hull[i].x};
          }
          all.back().reduce();
        }
      }
      std::sort(all.begin(), all.end());
      all.erase(std::unique(all.begin(), all.end()), all.end());
      for (auto &&e: all) axis[e]++;
    }
  }
  bool find = axis.empty();
  for (auto &&e: axis) {
    find |= e.second == layers;
  }
  puts(find ? "YES" : "NO");
  return 0;
}
