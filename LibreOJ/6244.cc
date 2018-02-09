#include <cstdio>
#include <vector>

using uint32 = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;
using uint128 = __uint128_t;

// Montgomery modular multiplication -- about 7x faster
// ensure mod is an odd number, use after call `set_mod` method
template<typename word, typename dword, typename sword>
struct UnsafeMod {
  UnsafeMod(): x(0) {}
  UnsafeMod(word _x): x(init(_x)) {}

  UnsafeMod& operator += (const UnsafeMod& rhs) {
    if ((x += rhs.x) >= mod) x -= mod;
    return *this;
  }
  UnsafeMod& operator -= (const UnsafeMod& rhs) {
    if (sword(x -= rhs.x) < 0) x += mod;
    return *this;
  }
  UnsafeMod& operator *= (const UnsafeMod& rhs) {
    x = reduce(dword(x) * rhs.x);
    return *this;
  }
  UnsafeMod operator + (const UnsafeMod &rhs) const {
    return UnsafeMod(*this) += rhs;
  }
  UnsafeMod operator - (const UnsafeMod &rhs) const {
    return UnsafeMod(*this) -= rhs;
  }
  UnsafeMod operator * (const UnsafeMod &rhs) const {
    return UnsafeMod(*this) *= rhs;
  }
  UnsafeMod pow(uint64 e) const {
    UnsafeMod ret(1);
    for (UnsafeMod base = *this; e; e >>= 1, base *= base) {
      if (e & 1) ret *= base;
    }
    return ret;
  }
  UnsafeMod inverse() const {
    return pow(mod - 2);
  }
  word get() const {
    return reduce(x);
  }

  static constexpr int word_bits = sizeof(word) * 8;
  static word modulus() {
    return mod;
  }
  static word init(word w) {
    return reduce(dword(w) * r2);
  }
  static void set_mod(word m) {
    mod = m;
    inv = mul_inv(mod);
    r2 = -dword(mod) % mod;
  }
  static word reduce(dword x) {
    word y = word(x >> word_bits) - word((dword(word(x) * inv) * mod) >> word_bits);
    return sword(y) < 0 ? y + mod : y;
  }
  static word mul_inv(word n, int e = 6, word x = 1) {
    return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
  }
  static word mod, inv, r2;

  word x;
};

using Mod = UnsafeMod<uint32, uint64, int>;
template <> uint32 Mod::mod = 0;
template <> uint32 Mod::inv = 0;
template <> uint32 Mod::r2 = 0;

using int64 = long long;

constexpr int N = 1e6 + 10;
constexpr int mod = 1e9 + 7;

int fact[N], ifact[N];

uint64 pow_mod(uint64 a, uint64 n) {
  uint64 r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

int main() {
  Mod::set_mod(mod);
  int n, k, x;
  scanf("%d%d%d", &n, &k, &x);
  fact[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fact[i] = (uint64)fact[i - 1] * i % mod;
  }
  ifact[n] = pow_mod(fact[n], mod - 2);
  for (int i = n; i; --i) {
    ifact[i - 1] = (uint64)ifact[i] * i % mod;
  }
  auto binom = [&](int n, int m) {
    return (uint64)fact[n] * ifact[m] % mod * ifact[n - m] % mod;
  };
  uint64 ret = 0;
  for (int i = 0; i <= k - x; ++i) {
    auto now = (uint64)ifact[k - x - i] * ifact[i] % mod * fact[n - x - i] % mod;
    if (i & 1) ret += mod - now;
    else ret += now;
  }
  ret %= mod;
  ret *= binom(k, x) * fact[k - x] % mod * ifact[n - k] % mod;
  printf("%llu\n", ret % mod);
  return 0;
}
