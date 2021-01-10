#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <map>
#include <algorithm>

using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

const int mod = 1e9 + 7;

// Montgomery modular multiplication -- about 7x faster
// ensure mod is an odd number, use after call `set_mod` method
template<typename word, typename dword, typename sword>
struct OddMod {
  OddMod(): x(0) {}
  OddMod(word _x): x(init(_x)) {}

  word get() const { return reduce(x); }
  bool operator == (const OddMod& rhs) const { return x == rhs.x; }
  bool operator != (const OddMod& rhs) const { return x != rhs.x; }
  OddMod operator * (const OddMod &rhs) const { return OddMod(*this) *= rhs; }
  OddMod operator + (const OddMod &rhs) const { return OddMod(*this) += rhs; }
  OddMod operator - (const OddMod &rhs) const { return OddMod(*this) -= rhs; }
  OddMod& operator *= (const OddMod& rhs) { x = reduce(dword(x) * rhs.x); return *this; }
  OddMod& operator += (const OddMod& rhs) { if ((x += rhs.x) >= mod) x -= mod; return *this; }
  OddMod& operator -= (const OddMod& rhs) { if (sword(x -= rhs.x) < 0) x += mod; return *this; }
  OddMod pow(u64 e) const {
    OddMod ret(1);
    for (OddMod base = *this; e; e >>= 1, base *= base) {
      if (e & 1) ret *= base;
    }
    return ret;
  }
  OddMod inverse() const { // make sure gcd(a, mod) == 1
    sword a = get(), b = mod;
    sword s = 1, t = 0;
    while (b) {
      auto q = a / b;
      std::swap(a -= q * b, b);
      std::swap(s -= q * t, t);
    }
    return s < 0 ? s + mod : s;
  }

  static constexpr int word_bits = sizeof(word) * 8;
  static word modulus() { return mod; }
  static word init(word w) { return reduce(dword(w) * r2); }
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

using mod_t = OddMod<u32, u64, int>;
template <> u32 mod_t::mod = 0;
template <> u32 mod_t::inv = 0;
template <> u32 mod_t::r2 = 0;

// works only when mod is a prime
template<class mod_t>
struct PolySum {
  static constexpr int N = 10000;
  mod_t fac[N], ifac[N];

  void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i;
    ifac[n] = fac[n].inverse();
    for (int i = n; i >= 1; --i) ifac[i - 1] = ifac[i] * i;
  }

  // Given a[0], a[1], ..., a[d],
  // Find the value of a[n] in O(d).
  mod_t eval(int d, mod_t *a, i64 n) {
    if (n < 0) return 0;
    if (n <= d) return a[n];
    std::vector<mod_t> m1(d + 1), m2(d + 1);
    m1[0] = m2[d] = 1;
    for (int i = 1; i <= d; ++i) {
      m1[i] = m1[i - 1] * ((n % mod - i + 1 + mod) % mod);
      m2[d - i] = m2[d - i + 1] * ((n % mod - d + i - 1 + mod) % mod);
    }
    mod_t ret = 0;
    for (int i = 0; i <= d; ++i) {
      auto val = a[i] * m1[i] * m2[i] * ifac[i] * ifac[d - i];
      if ((d - i) & 1) ret -= val;
      else ret += val;
    }
    return ret;
  }
};

struct Rem {
  i64 mul, r;
  mod_t w;
};

const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

mod_t binom[100][100];
PolySum<mod_t> poly;
std::vector<Rem> table[20];
std::vector<int> half[2];
std::map<i64, std::vector<std::pair<i64, mod_t>>> candidate[2];
mod_t psum[2000000][40];

std::vector<mod_t> prepare_poly(int k) {
  std::vector<mod_t> p = {0, 1};
  for (int i = 1; i <= k; ++i) {
    p.emplace_back(0);
    for (int j = i + 1; j >= 1; --j) {
      p[j] = p[j - 1] + p[j] * i;
    }
  }
  return p;
}

void prepare_table(int i, int k) {
  mod_t mod_p = mod_t(p[i]);
  int s = 1;
  while (s * p[i] <= k + 1) s *= p[i];
  std::vector<int> cnt((k + 1) * 64);
  std::vector<int> pe(s);
  for (int r = 0; r < s; ++r) {
    int mx = 0;
    for (int j = 0; j <= k; ++j) {
      int e = 0;
      for (int x = r + s + j; x % p[i] == 0; x /= p[i]) ++e;
      mx = std::max(mx, e), pe[r] += e;
    }
    pe[r] -= mx;
    cnt[pe[r]]++;
  }
  int mass = std::max_element(cnt.begin(), cnt.end()) - cnt.begin();
  mod_t inv = mod_p.pow(mod - 1 - mass);
  table[i].push_back((Rem){1, 0, inv});
  for (int r = 0; r < s; ++r) {
    mod_t w = mod_p.pow(mod - 1 - pe[r]) - inv;
    if (w.get()) table[i].push_back((Rem){s, r, w});
  }
}

void generate(int part, int d, i64 mul, i64 r, mod_t w) {
  if (d == (int)half[part].size()) {
    candidate[part][mul].emplace_back(r, w);
    return;
  }
  for (auto &e: table[half[part][d]]) {
    i64 n_mul = mul * e.mul;
    i64 n_r = r;
    while (n_r % e.mul != e.r) n_r += mul;
    generate(part, d + 1, n_mul, n_r, w * e.w);
  }
}

// mod should be not greater than 2^62 (about 4e18)
// return a * b % mod when mod is less than 2^31
inline i64 mul_mod(i64 a, i64 b, i64 mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  i64 k = (i64)((long double)a * b / mod);
  i64 res = a * b - k * mod;
  if (res < 0) res += mod;
  return res;
}

template<typename T>
T gcd(T a, T b) {
  return !b ? a : gcd(b, a % b);
}

// return x, where ax = 1 (mod mod)
i64 mod_inv(i64 a, i64 mod) {
  if (gcd(a, mod) != 1) return -1;
  i64 b = mod, s = 1, t = 0;
  while (b) {
    i64 q = a / b;
    std::swap(a -= q * b, b);
    std::swap(s -= q * t, t);
  }
  return s < 0 ? s + mod : s;
}

int main() {
  mod_t::set_mod(mod);

  i64 n, k;
  scanf("%lld%lld", &n, &k);
  poly.init(1000);
  int m = 0;
  while (p[m] <= k + 1) ++m;
  for (int i = 0; i < m; ++i) {
    prepare_table(i, k);
  }
  auto coef = prepare_poly(k);
  for (int i = 0; i <= k + 2; ++i) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
    }
  }

  int best = 0, best_mask = 0;
  for (int mask = 0; mask < (1 << m); ++mask) {
    int ls = 1, rs = 1;
    for (int i = 0; i < m; ++i) {
      if (mask >> i & 1) ls *= table[i].size();
      else rs *= table[i].size();
    }
    if (ls <= rs && ls > best) {
      best = ls;
      best_mask = mask;
    }
  }
  for (int i = 0; i < m; ++i) {
    if (best_mask >> i & 1) half[0].push_back(i);
    else half[1].push_back(i);
  }
  generate(0, 0, 1, 0, 1);
  generate(1, 0, 1, 0, 1);
  mod_t ret = 0;
  for (auto &e0: candidate[0]) for (auto &e1: candidate[1]) {
    i64 m1 = e0.first, m2 = e1.first, m = m1 * m2;
    i64 w1 = m2 * mod_inv(m2, m1), w2 = m1 * mod_inv(m1, m2);
    const auto &vs1 = e0.second, &vs2 = e1.second;
    static mod_t cache[2][1000], pw[1000];
    for (int i = 0; i <= k + 2; ++i) pw[i] = 1;
    for (int i = 0; i <= k + 1; ++i) {
      // sum(0^i+1^i+2^i+...)
      std::vector<mod_t> p(i + 2);
      for (int x = 0; x <= i + 1; ++x) {
        p[x] = pw[x];
        if (x) p[x] += p[x - 1];
      }
      cache[0][i] = poly.eval(i + 1, p.data(), n / m);
      cache[1][i] = poly.eval(i + 1, p.data(), n / m - 1);
      for (int x = 0; x <= k + 2; ++x) pw[x] *= x * m % mod;
    }
    std::vector<mod_t> mul0(k + 2), mul1(k + 2);
    for (int j = 0; j <= k + 1; ++j) {
      for (int i = j; i <= k + 1; ++i) {
        mul0[j] += coef.at(i) * binom[i][j] * cache[0][i - j];
        mul1[j] += coef[i] * binom[i][j] * cache[1][i - j];
      }
    }
    i64 r0 = n % m;
    std::vector<std::pair<i64, i64>> vs;
    for (auto &v: vs2) {
      i64 r2 = mul_mod(w2, v.first, m);
      vs.emplace_back(r2, v.second.get());
      vs.emplace_back(r2 - m, v.second.get());
    }
    std::sort(vs.begin(), vs.end());
    for (size_t i = 0; i < vs.size(); ++i) {
      mod_t w = vs[i].second, p = (vs[i].first % mod + mod) % mod;
      for (int j = 0; j <= k + 1; ++j) {
        psum[i + 1][j] = psum[i][j] + w;
        w *= p;
      }
    }
    for (auto &v1: vs1) {
      i64 r1 = mul_mod(w1, v1.first, m);
      int p1 = std::lower_bound(vs.begin(), vs.end(), std::make_pair(-r1, -1ll)) - vs.begin();
      int p2 = std::lower_bound(vs.begin(), vs.end(), std::make_pair(r0 + 1 - r1, -1ll)) - vs.begin();
      int p3 = std::lower_bound(vs.begin(), vs.end(), std::make_pair(m - r1, -1ll)) - vs.begin();
      static mod_t pw[1000];
      pw[0] = v1.second;
      for (int i = 1; i <= k + 1; ++i) {
        pw[i] = pw[i - 1] * mod_t(r1 % mod);
      }
      for (int j = 0; j <= k + 1; ++j) {
        mod_t s0 = 0, s1 = 0;
        for (int i = 0; i <= j; ++i) {
          s0 += (psum[p2][j - i] - psum[p1][j - i]) * binom[j][i] * pw[i];
          s1 += (psum[p3][j - i] - psum[p2][j - i]) * binom[j][i] * pw[i];
        }
        ret += mul0[j] * s0, ret += mul1[j] * s1;
      }
    }
  }
  printf("%u\n", ret.get());
  return 0;
}
