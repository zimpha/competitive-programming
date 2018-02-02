#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>

using int64 = long long;
using uint64 = unsigned long long;
using uint32 = unsigned int;

struct bits {
  bits() = delete;

  constexpr static uint32 popcount(uint32 x) {
    return __builtin_popcount(x);
  }

  constexpr static uint32 popcount(uint64 x) {
    return __builtin_popcountll(x);
  }

  constexpr static uint32 clz(uint32 x) {
    return __builtin_clz(x);
  }

  constexpr static uint32 clz(uint64 x) {
    return __builtin_clzll(x);
  }

  constexpr static uint32 ctz(uint32 x) {
    return __builtin_ctz(x);
  }

  constexpr static uint32 ctz(uint64 x) {
    return __builtin_ctzll(x);
  }

  constexpr static uint32 ilog2(uint32 x) {
    return 31 - clz(x);
  }

  constexpr static uint32 ilog2(uint64 x) {
    return 63 - clz(x);
  }
};

template<typename word, typename dword>
struct FastDivision {
  constexpr static int word_bits = sizeof(word) * 8;

  FastDivision() = default;
  FastDivision(word n): m(n) {
    if (n == 1) {
      x = 1;
      shamt = 0;
    } else {
      shamt = bits::ilog2(n - 1) + word_bits;
      x = ((dword(1) << shamt) + n - 1) / n;
    }
  }

  friend word operator / (const word &n, const FastDivision &d) {
    return dword(n) * d.x >> d.shamt;
  }

  friend word operator % (const word &n, const FastDivision &d) {
    return n - n / d * d.m;
  }

private:
  int shamt;
  word m, x;
};

template<typename word>
struct ExactDivisor {
  ExactDivisor() = default;
  ExactDivisor(const word &n): t(word(-1) / n), i(mul_inv(n)) {}

  constexpr static word mul_inv(word n, int e = 6, word x = 1) {
    return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
  }

  friend word operator / (const word &n, const ExactDivisor &d) {
    return n * d.i;
  }

  bool divide(const word &n) const {
    return n * i <= t;
  }

private:
  word t, i;
};

template<typename word, typename dword, typename sword>
struct Mod {
  Mod(): x(0) {}
  Mod(word _x): x(init(_x)) {}

  Mod& operator += (const Mod& rhs) {
    if ((x += rhs.x) >= mod) x -= mod;
    return *this;
  }
  Mod& operator -= (const Mod& rhs) {
    if (sword(x -= rhs.x) < 0) x += mod;
    return *this;
  }
  Mod& operator *= (const Mod& rhs) {
    x = reduce(dword(x) * rhs.x);
    return *this;
  }
  Mod operator + (const Mod &rhs) const {
    return Mod(*this) += rhs;
  }
  Mod operator - (const Mod &rhs) const {
    return Mod(*this) -= rhs;
  }
  Mod operator * (const Mod &rhs) const {
    return Mod(*this) *= rhs;
  }
  Mod pow(uint64 e) const {
    Mod ret(1);
    for (Mod base = *this; e; e >>= 1, base *= base) {
      if (e & 1) ret *= base;
    }
    return ret;
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
  static word reduce(dword x) {
    word y = word(x >> word_bits) - word((dword(word(x) * inv) * mod) >> word_bits);
    return sword(y) < 0 ? y + mod : y;
  }
  static word mul_inv(word n, int e = 6, word x = 1) {
    return !e ? x : mul_inv(n, e - 1, x * (2 - x * n));
  }
  constexpr static word mod = 1e8 + 7;
  constexpr static word inv = 3295526071u;
  constexpr static word r2 = 37556848;

  word x;
};

using FastDiv32 = FastDivision<uint32, uint64>;
using ExactDiv32 = ExactDivisor<uint32>;
using Mod32 = Mod<uint32, uint64, int>;

constexpr int S = 65536;

FastDiv32 divp[S];
uint32 p[S], m;
bool mark[S];

void prepare(int n) {
  for (int i = 2; i <= n; ++i) if (!p[i]) {
    divp[m] = FastDiv32(i);
    p[m++] = i;
    for (int j = i + i; j <= n; j += i) p[j] = 1;
  }
}

int main() {
  uint32 n;
  scanf("%u", &n);
  if (n <= 3) {
    if (n == 1) puts("1");
    else if (n == 2) puts("2");
    else puts("6");
    return 0;
  }
  uint32 sqrt_n = sqrt(n);
  prepare(sqrt_n);
  Mod32 one{1}, res{1}, now{sqrt_n};
  int bound = 0;
  for (uint32 l = sqrt_n + 1; l <= n; l += S) {
    uint32 r = std::min(n + 1, l + S);
    while (bound < m && p[bound] * p[bound] < r) ++bound;
    for (int i = l; i < r; ++i) mark[i - l] = 0;
    for (int i = l + (l & 1); i < r; i += 2) mark[i - l] = 1;
    for (int i = 1; i < bound; ++i) {
      int pp = p[i], p2 = pp + pp;
      int k = (l + pp - 1) / divp[i];
      if (~k & 1) ++k;
      for (uint32 x = k * pp; x < r; x += p2) {
        mark[x - l] = 1;
      }
    }
    for (int i = l; i < r; ++i) {
      now += one;
      if (!mark[i - l]) res *= now;
    }
  }
  for (int i = 0; i < m; ++i) {
    uint32 cnt = 0, v = 1, u = n / p[i];
    for (; v <= u; v *= p[i]) ++cnt;
    res *= v;
  }
  printf("%u\n", res.get());
  return 0;
}
