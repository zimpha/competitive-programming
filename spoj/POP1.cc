#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>
#include <vector>
#include <ostream>

#define _rep(_1, _2, _3, _4, name, ...) name
#define rep2(i, n) rep3(i, 0, n)
#define rep3(i, a, b) rep4(i, a, b, 1)
#define rep4(i, a, b, c) for (int i = int(a); i < int(b); i += int(c))
#define rep(...) _rep(__VA_ARGS__, rep4, rep3, rep2, _)(__VA_ARGS__)

using namespace std;

using i64 = long long;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using f80 = long double;

namespace factor {

using u128 = __uint128_t;

template <typename word, typename dword, typename sword>
struct Mod {
  Mod() : n_(0) {}
  Mod(word n) : n_(init(n)) {}

  static constexpr int word_bits = sizeof(word) * 8;
  static void set_mod(word m) { mod = m, inv = mul_inv(m), r2 = -dword(m) % m; }
  static word mul_inv(word n) {
    word x = n;
    rep(_, 5) x *= 2 - n * x;
    return x;
  }
  static word reduce(dword w) {
    word y = (w >> word_bits) - ((dword(word(w) * inv) * mod) >> word_bits);
    return sword(y) < 0 ? y + mod : y;
  }
  static word init(word n) { return reduce(u128(n) * r2); }
  static word ilog2(word n) { return (n == 0) ? 0 : __lg(n); }

  Mod& operator += (Mod rhs) { if ((n_ += rhs.n_) >= mod) n_ -= mod; return *this; }
  Mod& operator -= (Mod rhs) { if (sword(n_ -= rhs.n_) < 0) n_ += mod; return *this; }
  Mod& operator *= (Mod rhs) { n_ = reduce(u128(n_) * rhs.n_); return *this; }

  bool operator == (Mod rhs) { return n_ == rhs.n_; }
  bool operator != (Mod rhs) { return !(*this == rhs); }

  Mod operator + (Mod rhs) { return Mod(*this) += rhs; }
  Mod operator - (Mod rhs) { return Mod(*this) -= rhs; }
  Mod operator * (Mod rhs) { return Mod(*this) *= rhs; }

  Mod operator - () { return Mod() - *this; };

  Mod pow(word e) {
    Mod ret = Mod(1), base = *this;
    for (; e; e >>= 1, base *= base) {
      if (e & 1) ret *= base;
    }
    return ret;
  }
  word val() { return reduce(n_); }
  friend ostream& operator << (ostream& os, Mod& m) { return os << m.val(); }

  word n_;
  static word mod, inv, r2;
};
using m64 = Mod<u64, u128, i64>;
using m32 = Mod<u32, u64, int>;
template <> u32 m32::mod = 0;
template <> u32 m32::inv = 0;
template <> u32 m32::r2 = 0;
template <> u64 m64::mod = 0;
template <> u64 m64::inv = 0;
template <> u64 m64::r2 = 0;

template <typename word, typename mod>
u32 composite(word n, word d, int s, const u32* bases, int base_size) {
  mod::set_mod(n);
  mod one = mod(1), minus_one = -one;
  rep(i, base_size) {
    mod b = mod(bases[i]).pow(d);
    if (b == one || b == minus_one) continue;
    int t = s - 1;
    for (; t > 0; --t) if ((b *= b) == minus_one) break;
    if (t == 0) return bases[i];
  }
  return false;
}

bool miller_rabin(u64 n) {
  static const u32 bases[][7] {
    {2, 3},
    {2, 299417},
    {2, 7, 61},
    {15, 176006322, u32(4221622697)},
    {2, 2570940, 211991001, u32(3749873356)}, 
    {2, 2570940, 880937, 610386380, u32(4130785767)}, 
    {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
  };
  if (n <= 1) return false;
  if (!(n & 1)) return n == 2;
  if (n <= 8) return true;

  u64 d = n - 1;
  u64 s = __builtin_ctzll(d);
  d >>= s;

  u32 base_id = 6, base_size = 7;
  if (n < 1373653) {
    base_id = 0, base_size = 2;
  } else if (n < 19471033) {
    base_id = 1, base_size = 2;
  } else if (n < u64(4759123141)) {
    base_id = 2, base_size = 3;
  } else if (n < u64(154639673381)) {
    base_id = 3, base_size = 3;
  } else if (n < u64(47636622961201)) {
    base_id = 4, base_size = 4;
  } else if (n < u64(3770579582154547)) {
    base_id = 5, base_size = 5;
  } 

  if (n < (u32(1) << 31)) {
    return !composite<u32, m32>(n, d, s, bases[base_id], base_size);
  } else if (n < (u64(1) << 63)) {
    return !composite<u64, m64>(n, d, s, bases[base_id], base_size);
  } else assert(0);

  return true;
}

struct ExactDiv {
  ExactDiv() {}
  ExactDiv(u64 n) : n(n), i(m64::mul_inv(n)), t(u64(-1) / n) {}
  friend u64 operator / (u64 n, ExactDiv d) { return n * d.i; };
  bool divide(u64 n) { return n / *this <= t; }
  u64 n, i, t;
};

vector<ExactDiv> primes;

void init(u32 n) {
  u32 sqrt_n = sqrt(n);
  vector<u8> isprime(n + 1, 1);
  rep(i, 2, sqrt_n + 1) if (isprime[i]) rep(j, i * i, n + 1, i) isprime[j] = 0;

  primes.clear();
  rep(i, 2, n + 1) if (isprime[i]) primes.push_back(ExactDiv(i));
}

u64 square(u64 n) {
  return n * n;
}

bool is_prime(u64 n) {
  if (n <= 1) return false;
  if (!(n & 1)) return n == 2;
  rep(i, 1, primes.size()) {
    auto p = primes[i];
    if (square(p.n) > n) return true;
    if (p.divide(n)) return n == p.n;
  }
  return miller_rabin(n);
}

u64 next_prime(u64 n) {
  if (n <= 1) return 2;
  if (n <= 2) return 3;
  for (n = (n + 1) / 2 * 2 + 1; !is_prime(n); n += 2);
  return n;
}

} // namespace factor

bool check(int n) {
  static int d[20];
  static bool dp[20];
  int m = 0;
  while (n) {
    dp[m] = 0;
    d[m++] = n % 10;
    n /= 10;
  }
  n = 0;
  for (int i = m - 1; i >= 1; --i) {
    n = n * 10 + d[i];
    dp[i] |= factor::is_prime(n);
    if (!dp[i] || !d[i - 1]) continue;
    int v = 0;
    for (int j = i - 1; j >= 0; --j) {
      v = v * 10 + d[j];
      dp[j] |= factor::is_prime(v);
    }
  }
  return dp[0];
}

int main() {
  factor::init(512);
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    if (n <= 23) puts("23");
    else {
      n -= 1;
      while (true) {
        n = factor::next_prime(n);
        if (check(n)) break;
      }
      printf("%d\n", n);
    }
  }
  return 0;
}
