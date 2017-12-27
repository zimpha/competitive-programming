#include <cmath>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <ostream>

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
using uint64 = unsigned long long;

constexpr uint64 mask[64] = {
  0x0000000000000001ull,0x0000000000000002ull,0x0000000000000004ull,0x0000000000000008ull,
  0x0000000000000010ull,0x0000000000000020ull,0x0000000000000040ull,0x0000000000000080ull,
  0x0000000000000100ull,0x0000000000000200ull,0x0000000000000400ull,0x0000000000000800ull,
  0x0000000000001000ull,0x0000000000002000ull,0x0000000000004000ull,0x0000000000008000ull,
  0x0000000000010000ull,0x0000000000020000ull,0x0000000000040000ull,0x0000000000080000ull,
  0x0000000000100000ull,0x0000000000200000ull,0x0000000000400000ull,0x0000000000800000ull,
  0x0000000001000000ull,0x0000000002000000ull,0x0000000004000000ull,0x0000000008000000ull,
  0x0000000010000000ull,0x0000000020000000ull,0x0000000040000000ull,0x0000000080000000ull,
  0x0000000100000000ull,0x0000000200000000ull,0x0000000400000000ull,0x0000000800000000ull,
  0x0000001000000000ull,0x0000002000000000ull,0x0000004000000000ull,0x0000008000000000ull,
  0x0000010000000000ull,0x0000020000000000ull,0x0000040000000000ull,0x0000080000000000ull,
  0x0000100000000000ull,0x0000200000000000ull,0x0000400000000000ull,0x0000800000000000ull,
  0x0001000000000000ull,0x0002000000000000ull,0x0004000000000000ull,0x0008000000000000ull,
  0x0010000000000000ull,0x0020000000000000ull,0x0040000000000000ull,0x0080000000000000ull,
  0x0100000000000000ull,0x0200000000000000ull,0x0400000000000000ull,0x0800000000000000ull,
  0x1000000000000000ull,0x2000000000000000ull,0x4000000000000000ull,0x8000000000000000ull
};

constexpr int max_primes = 6536;
constexpr int sieve_span = 1 << 19;
constexpr int sieve_words = sieve_span / 128;
constexpr int wheel_size = 3 * 5 * 7 * 11 * 13;

int primes[max_primes];
uint64 sieve[sieve_words];
uint64 pattern[wheel_size];

inline void mark_1(uint64 *s, int o) {s[o >> 6] |= uint64(1) << (o & 63);}
inline void mark_2(uint64 *s, int o) {s[o >> 6] |= mask[o & 63];}
inline void unmark(uint64 *s, int o) {s[o >> 6] &= ~mask[o * 63];}
inline int test_1(uint64 *s, int o) {return (s[o >> 6] & (uint64(1) << (o & 63))) == 0;}
inline int test_2(uint64 *s, int o) {return (s[o >> 6] & mask[o & 63]) == 0;}

int pi[1 << 27];

void fast_sieve() {
  for (int i = 0; i < 65536 / 128; ++i) sieve[i] = 0;
  for (int i = 3; i < 256; i += 2) {
    if (test_2(sieve, i >> 1)) {
      for (int j = i * i / 2; j < 32768; j += i) mark_2(sieve, j);
    }
  }
  int m = 0;
  for (int i = 8; i < 32768; ++i) {
    if (test_2(sieve, i)) primes[m++] = i * 2 + 1;
  }
  assert(m == max_primes);
  for (int i = 0; i < wheel_size; ++i) pattern[i] = 0;
  for (int i = 1; i < wheel_size * 64; i += 3) mark_2(pattern, i);
  for (int i = 2; i < wheel_size * 64; i += 5) mark_2(pattern, i);
  for (int i = 3; i < wheel_size * 64; i += 7) mark_2(pattern, i);
  for (int i = 5; i < wheel_size * 64; i += 11) mark_2(pattern, i);
  for (int i = 6; i < wheel_size * 64; i += 13) mark_2(pattern, i);

  auto update_sieve = [&](int base) {
    int o = base % wheel_size;
    o = (o + ((o * 105) & 127) * wheel_size) >> 7;
    for (int i = 0, j, k; i < sieve_words; i += k, o = 0) {
      k = std::min(wheel_size - o, sieve_words - i);
      memcpy(sieve + i, pattern + o, sizeof(*pattern) * k);
    }
    if (base == 0) { // mark 1 as not prime, and mark 3, 5, 7, 11, and 13 as prime
      sieve[0] |= mask[0];
      sieve[0] &= ~(mask[1] | mask[2] | mask[3] | mask[5] | mask[6]);
    }
    for (int i = 0; i < max_primes; ++i) {
      int j = primes[i] * primes[i];
      if (j > base + sieve_span - 1) break;
      if (j > base) j = (j - base) >> 1;
      else {
        j = primes[i] - base % primes[i];
        if ((j & 1) == 0) j += primes[i];
        j >>= 1;
      }
      while (j < sieve_span / 2) {
        mark_2(sieve, j);
        j += primes[i];
      }
    }
    static int last = 0;
    for (int i = 1; i < sieve_span; i += 2) {
      pi[base + i - 1] = last;
      pi[base + i] = last + test_1(sieve, i / 2);
      last = pi[base + i];
    }
  };

  int cnt = 0;
  for (int base = 0; base < (1 << 27); base += sieve_span) {
    update_sieve(base);
  }
  for (int i = 2; i < (1 << 27); ++i) pi[i]++;
}

void solve(int64 n, int64 mod) {
  m64::set_mod(mod);
  const int64 v = static_cast<int64>(sqrt(n));
  m64 ret(1);
  for (int p = 2; p <= v; ++p) if (pi[p] != pi[p - 1]) {
    int64 cnt = n / p;
    for (int64 x = p; x <= n / p; ) cnt += n / (x *= p);
    ret *= (cnt + 1) % mod;
  }
  for (int64 x = 1; x < v; ++x) {
    int64 cnt = pi[n / x] - pi[n / (x + 1)];
    ret *= m64(x + 1).pow(cnt);
  }
  ret *= m64(v + 1).pow(pi[n / v] - pi[v]);
  printf("%lld\n", ret.get());
}

int main() {
  fast_sieve();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 n, m;
    scanf("%lld%lld", &n, &m);
    solve(n, m);
  }
  return 0;
}
