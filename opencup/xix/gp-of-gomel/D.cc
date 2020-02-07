#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

using int64 = long long;

const int mod = 998244353;
const int i2 = 499122177;
const int i6 = 166374059;

// ax + b
struct Poly {
  int64 a, b;
  int l, r;
};

struct Event {
  int64 a, b;
  int l;
  bool operator < (const Event &rhs) const {
    return l < rhs.l;
  }
};

std::vector<Poly> conv(const std::vector<Poly> &f) {
  std::vector<Event> ev;
  for (auto &u: f) for (auto &v: f) {
    int d = std::min(u.r - u.l, v.r - v.l);
    int l1 = u.l + v.l, r1 = u.l + v.l + d - 1;
    int l2 = u.r + v.r - d + 1, r2 = u.r + v.r;
    // u.l + u.r, u.l + u.r + d - 1
    if (l1 <= r1) {
      ev.push_back((Event){1, 1 - l1, l1});
      ev.push_back((Event){-1, l1 - 1, r1 + 1});
    }
    if (r1 + 1 <= l2 - 1) {
      ev.push_back((Event){0, d + 1, r1 + 1});
      ev.push_back((Event){0, -1 - d, l2});
    }
    if (l2 <= r2) {
      ev.push_back((Event){-1, r2 + 1, l2});
      ev.push_back((Event){1, -1 - r2, r2 + 1});
    }
  }
  std::sort(ev.begin(), ev.end());
  int64 a = 0, b = 0;
  std::vector<Poly> ret;
  for (size_t i = 0, j = 0; i < ev.size(); i = j) {
    for (j = i; j < ev.size() && ev[i].l == ev[j].l; ++j) {
      a += ev[j].a, b += ev[j].b;
    }
    a %= mod; if (a < 0) a += mod;
    b %= mod; if (b < 0) b += mod;
    if (a || b) {
      assert(j != ev.size());
      ret.push_back((Poly){a, b, ev[i].l, ev[j].l - 1});
    }
  }
  return ret;
}

// A^4(x) - 6A(x^2)A^2(x) + 3A^2(x^2) + 8A(x^3)A(x) - 6A(x^4)
int main() {
  int n, s;
  scanf("%d%d", &n, &s);
  std::vector<Poly> f(n);
  for (int i = 0; i < n; ++i) {
    f[i].a = 0; f[i].b = 1;
    scanf("%d%d", &f[i].l, &f[i].r);
  }
  int64 ret = 0;
  // A(x^4)
  if (s % 4 == 0) {
    for (const auto &p: f) if (p.l <= s / 4 && s / 4 <= p.r) {
      ret -= 6;
    }
  }
  // A(x^3)A(x)
  for (const auto &u: f) for (const auto &v: f) {
    int l = u.l, r = u.r;
    if (s - v.l >= 0) r = std::min(r, (s - v.l) / 3);
    else r = -1;
    if (s - v.r >= 0) l = std::max(l, (s - v.r + 2) / 3);
    if (l <= r) ret += (int64)8 * (r - l + 1) % mod;
  }
  // A^2(x^2)
  if (s % 2 == 0) {
    for (const auto &u: f) for (const auto &v: f) {
      int l = std::max(u.l, s / 2 - v.r), r = std::min(u.r, s / 2 - v.l);
      if (l <= r) ret += (int64)3 * (r - l + 1) % mod;
    }
  }
  auto g = conv(f);
  // A(x^2)A^2(x)
  for (int i = 0, j = n - 1; i < (int)g.size();) {
    int l = s - g[i].r, r = s - g[i].l;
    while (j >= 0 && f[j].l * 2 > r) --j;
    if (j >= 0 && f[j].r * 2 >= l) {
      int ll = std::max(g[i].l, s - f[j].r * 2);
      int rr = std::min(g[i].r, s - f[j].l * 2);
      if (ll % 2 != s % 2) ++ll;
      if (rr % 2 != s % 2) --rr;
      if (ll <= rr) {
        int e = ll % 2;
        ll /= 2, rr /= 2;
        ret -= 6 * (g[i].b + g[i].a * e) % mod * (rr - ll + 1) % mod + 6 * g[i].a % mod * (rr + ll) % mod * (rr - ll + 1) % mod;
      }
      if (f[j].l * 2 >= l) --j;
      else ++i;
    } else {
      ++i;
    }
  }
  // A^4(x)
  for (int i = 0, j = g.size() - 1; i < (int)g.size(); ) {
    int l = s - g[i].r, r = s - g[i].l;
    while (j >= 0 && g[j].l > r) --j;
    if (j >= 0 && g[j].r >= l) {
      int ll = std::max(g[i].l, s - g[j].r), rr = std::min(g[i].r, s - g[j].l);
      int64 a = mod - g[i].a * g[j].a % mod;
      int64 b = g[i].a * (g[j].b + g[j].a * s % mod) % mod - g[j].a * g[i].b % mod;
      if (b < 0) b += mod;
      int64 c = g[i].b * (g[j].b + g[j].a * s % mod) % mod;
      ret += c * (rr - ll + 1) % mod;
      ret += b * (rr - ll + 1) % mod * (ll + rr) % mod * i2 % mod;
      ret += a * rr % mod * (2 * rr + 1) % mod * (rr + 1) % mod * i6 % mod;
      if (ll) --ll;
      ret -= a * ll % mod * (2 * ll + 1) % mod * (ll + 1) % mod * i6 % mod;
      if (g[j].l >= l) --j;
      else ++i;
    } else {
      ++i;
    }
  }
  ret %= mod; ret += mod; ret %= mod;
  ret = ret * i6 % mod * i2 % mod * i2 % mod;
  printf("%lld\n", ret);
  return 0;
}
