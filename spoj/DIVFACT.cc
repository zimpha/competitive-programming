#include <cmath>
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <ostream>

const int mod = 1e9 + 7;

using i64 = long long;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;

struct Mod64 {
  using u128 = __uint128_t;

  Mod64() : n_(0) {}
  Mod64(u64 n) : n_(init(n)) {}

  static void set_mod(u64 m) {
    shift = __builtin_ctzll(m);
    mask = (u64(1) << shift) - 1;
    mod = m >> shift; assert(mod & 1);
    inv = mod;
    for (int i = 0; i < 5; ++i) inv *= 2 - inv * mod;
    assert(mod * inv == 1);
    r2 = -u128(mod) % mod;
    one = u64(1) << shift | 1;
  }
  static u64 modulus() { return mod << shift; }

  static u64 init(u64 x) {
    return reduce_odd(u128(x) * r2) << shift | (x & mask);
  }
  static u64 reduce_odd(u128 x) {
    u64 y = u64(x >> 64) - u64((u128(u64(x) * inv) * mod) >> 64);
    return i64(y) < 0 ? y + mod : y;
  }
  static u64 reduce(u64 x0, u64 x1) {
    u64 y = reduce_odd(u128(x0 >> shift) * (x1 >> shift));
    return y << shift | ((x0 * x1) & mask);
  }
  Mod64& operator += (Mod64 rhs) {
    u64 hi = (n_ >> shift) + (rhs.n_ >> shift) - mod;
    if (i64(hi) < 0) hi += mod;
    n_ = hi << shift | ((n_ + rhs.n_) & mask);
    return *this;
  }
  Mod64& operator -= (Mod64 rhs) {
    u64 hi = (n_ >> shift) - (rhs.n_ >> shift);
    if (i64(hi) < 0) hi += mod;
    n_ = hi << shift | ((n_ - rhs.n_) & mask);
    return *this;
  }
  Mod64& operator *= (Mod64 rhs) { n_ = reduce(n_, rhs.n_); return *this; }
  Mod64 operator + (Mod64 rhs) const { return Mod64(*this) += rhs; }
  Mod64 operator - (Mod64 rhs) const { return Mod64(*this) -= rhs; }
  Mod64 operator * (Mod64 rhs) const { return Mod64(*this) *= rhs; }
  u64 get() const {
    u64 ret = reduce(n_, one);
    u64 r1 = ret >> shift;
    return mod * (((ret - r1) * inv) & mask) + r1;
  }
  void set(u64 n) { n_ = n; }
  Mod64 pow(u64 exp) const {
    Mod64 ret = Mod64(1);
    for (Mod64 base = *this; exp; exp >>= 1, base *= base) if (exp & 1) ret *= base;
    return ret;
  }
  Mod64 inverse() const { return pow(mod - 2); }
  static u64 mod, inv, r2, mask, one;
  static int shift;
  u64 n_;
};
u64 Mod64::mod, Mod64::inv, Mod64::r2, Mod64::mask, Mod64::one;
int Mod64::shift;

using m64 = Mod64;
using int64 = long long;

void solve(int64 n) {
  m64::set_mod(mod);
  const int64 v = static_cast<int64>(sqrt(n));
  std::vector<int64> ssum(v + 1), lsum(v + 1);
  for (int i = 1; i <= v; ++i) {
    ssum[i] = i - 1;
    lsum[i] = n / i - 1;
  }
  for (int64 p = 2; p <= v; ++p) {
    if (ssum[p] == ssum[p - 1]) continue;
    int64 psum = ssum[p - 1], q = p * p, ed = std::min(v, n / q);
    for (int i = 1; i <= ed; ++i) {
      int64 d = i * p;
      if (d <= v) {
        lsum[i] -= lsum[d] - psum;
      } else {
        lsum[i] -= ssum[n / d] - psum;
      }
    }
    for (int64 i = v; i >= q; --i) {
      ssum[i] -= ssum[i / p] - psum;
    }
  }
  m64 ret(1);
  for (int p = 2; p <= v; ++p) if (ssum[p] != ssum[p - 1]) {
    int64 cnt = n / p;
    for (int64 x = p; x <= n / p; ) cnt += n / (x *= p);
    ret *= (cnt + 1) % mod;
  }
  for (int64 x = 1; x < v; ++x) {
    int64 cnt = lsum[x] - lsum[x + 1];
    ret *= m64(x + 1).pow(cnt);
  }
  ret *= m64(v + 1).pow(lsum[v] - ssum[v]);
  printf("%lld\n", ret.get());
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n;
    scanf("%lld", &n);
    solve(n);
  }
  return 0;
}
