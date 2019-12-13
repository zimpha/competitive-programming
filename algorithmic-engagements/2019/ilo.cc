#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>

using int64 = long long;
using uint32 = unsigned int;
using uint64 = unsigned long long;

// if mod is not close to 2^(word_bits-1), it's faster to use comment lines
template <class word, class dword, class sword, word mod, word root>
class Mod {
public:
  static constexpr word mul_inv(word n, int e = 6, word x = 1) {
    return e == 0 ? x : mul_inv(n, e - 1, x * (2 - x * n));
  }

  static constexpr word inv = mul_inv(mod);
  static constexpr word r2 = -dword(mod) % mod;
  static constexpr int word_bits = sizeof(word) * 8;
  static constexpr int level = __builtin_ctzll(mod - 1);

  static word modulus() {
    return mod;
  }
  static word init(const word& w) {
    return reduce(dword(w) * r2);
  }
  static word reduce(const dword& w) {
    word y = word(w >> word_bits) - word((dword(word(w) * inv) * mod) >> word_bits);
    return sword(y) < 0 ? y + mod : y;
    //return word(w >> word_bits) + mod - word((dword(word(w) * inv) * mod) >> word_bits);
  }
  static Mod omega() {
    return Mod(root).pow((mod - 1) >> level);
  }

  Mod() = default;
  Mod(const word& n): x(init(n)) {};
  Mod& operator += (const Mod& rhs) {
    //this->x += rhs.x;
    if ((x += rhs.x) >= mod) x -= mod;
    return *this;
  }
  Mod& operator -= (const Mod& rhs) {
    //this->x += mod * 3 - rhs.x;
    if (sword(x -= rhs.x) < 0) x += mod;
    return *this;
  }
  Mod& operator *= (const Mod& rhs) {
    this->x = reduce(dword(this->x) * rhs.x);
    return *this;
  }
  Mod operator + (const Mod& rhs) const {
    return Mod(*this) += rhs;
  }
  Mod operator - (const Mod& rhs) const {
    return Mod(*this) -= rhs;
  }
  Mod operator * (const Mod& rhs) const {
    return Mod(*this) *= rhs;
  }
  word get() const {
    return reduce(this->x) % mod;
  }
  Mod inverse() const {
    return pow(mod - 2);
  }
  Mod pow(word e) const {
    Mod ret(1);
    for (Mod a = *this; e; e >>= 1) {
      if (e & 1) ret *= a;
      a *= a;
    }
    return ret;
  }
  word x;
};

template <class T>
inline void sum_diff(T& x, T &y) {
  auto a = x, b = y;
  x = a + b, y = a - b;
}

// transform with dif, itransform with dft, no need to use bit_rev
namespace ntt_fast {
template <typename mod_t>
void transform(mod_t* A, int n, const mod_t* roots, const mod_t* iroots) {
  const int logn = __builtin_ctz(n), nh = n >> 1, lv = mod_t::level;
  auto one = mod_t(1), im = roots[lv - 2];
  mod_t dw[lv - 1]; dw[0] = roots[lv - 3];
  for (int i = 1; i < lv - 2; ++i) {
    dw[i] = dw[i - 1] * iroots[lv - 1 - i] * roots[lv - 3 - i];
  }
  dw[lv - 2] = dw[lv - 3] * iroots[1];
  if (logn & 1) for (int i = 0; i < nh; ++i) {
    sum_diff(A[i], A[i + nh]);
  }
  for (int e = logn & ~1; e >= 2; e -= 2) {
    const int m = 1 << e, m4 = m >> 2;
    auto w2 = one;
    for (int i = 0; i < n; i += m) {
      auto w1 = w2 * w2, w3 = w1 * w2;
      for (int j = i; j < i + m4; ++j) {
        auto a0 = A[j + m4 * 0] * one, a1 = A[j + m4 * 1] * w2;
        auto a2 = A[j + m4 * 2] * w1,  a3 = A[j + m4 * 3] * w3;
        auto t02p = a0 + a2, t13p = a1 + a3;
        auto t02m = a0 - a2, t13m = (a1 - a3) * im;
        A[j + m4 * 0] = t02p + t13p; A[j + m4 * 1] = t02p - t13p;
        A[j + m4 * 2] = t02m + t13m; A[j + m4 * 3] = t02m - t13m;
      }
      w2 *= dw[__builtin_ctz(~(i >> e))];
    }
  }
}

template <typename mod_t>
void itransform(mod_t* A, int n, const mod_t* roots, const mod_t* iroots) {
  const int logn = __builtin_ctz(n), nh = n >> 1, lv = mod_t::level;
  const auto one = mod_t(1), im = iroots[lv - 2];
  mod_t dw[lv - 1]; dw[0] = iroots[lv - 3];
  for (int i = 1; i < lv - 2; ++i) {
    dw[i] = dw[i - 1] * roots[lv - 1 - i] * iroots[lv - 3 - i];
  }
  dw[lv - 2] = dw[lv - 3] * roots[1];
  for (int e = 2; e <= logn; e += 2) {
    const int m = 1 << e, m4 = m >> 2;
    auto w2 = one;
    for (int i = 0; i < n; i += m) {
      const auto w1 = w2 * w2, w3 = w1 * w2;
      for (int j = i; j < i + m4; ++j) {
        auto a0 = A[j + m4 * 0], a1 = A[j + m4 * 1];
        auto a2 = A[j + m4 * 2], a3 = A[j + m4 * 3];
        auto t01p = a0 + a1, t23p = a2 + a3;
        auto t01m = a0 - a1, t23m = (a2 - a3) * im;
        A[j + m4 * 0] = (t01p + t23p) * one; A[j + m4 * 2] = (t01p - t23p) * w1;
        A[j + m4 * 1] = (t01m + t23m) * w2;  A[j + m4 * 3] = (t01m - t23m) * w3;
      }
      w2 *= dw[__builtin_ctz(~(i >> e))];
    }
  }
  if (logn & 1) for (int i = 0; i < nh; ++i) {
    sum_diff(A[i], A[i + nh]);
  }
}

template <typename mod_t>
void convolute(mod_t* A, int n, mod_t* B, int m, bool cyclic=false) {
  const int s = cyclic ? std::max(n, m) : n + m - 1;
  const int size = 1 << (31 - __builtin_clz(2 * s - 1));
  mod_t roots[mod_t::level], iroots[mod_t::level];
  roots[0] = mod_t::omega();
  for (int i = 1; i < mod_t::level; ++i) {
    roots[i] = roots[i - 1] * roots[i - 1];
  }
  iroots[0] = roots[0].inverse();
  for (int i = 1; i < mod_t::level; ++i) {
    iroots[i] = iroots[i - 1] * iroots[i - 1];
  }
  std::fill(A + n, A + size, 0); transform(A, size, roots, iroots);
  const auto inv = mod_t(size).inverse();
  if (A == B && n == m) {
    for (int i = 0; i < size; ++i) A[i] *= A[i] * inv;
  } else {
    std::fill(B + m, B + size, 0); transform(B, size, roots, iroots);
    for (int i = 0; i < size; ++i) A[i] *= B[i] * inv;
  }
  itransform(A, size, roots, iroots);
}
}

// 377487361 = 2 ^ 23 * 45 + 1
using mod_t = Mod<uint32, uint64, int, 377487361, 7>;

const int N = 1 << 21;

int a[N], b[N], t[N];
int64 f[N], tf[N], sf[N];
int64 fibs[100];

mod_t A[N], RA_odd[N], RA_even[N];
mod_t B[N], RB_odd[N], RB_even[N];

void apply(int n, int m) {
  if (n > m) std::swap(n, m);
  int r = n + m + 2, l = r - 4 * (n / 2);
  assert(l >= 2);
  sf[l]++; sf[r]--;
  if (n % 2 == 1) {
    if (n == m) tf[2]++;
    else tf[m - n + 1]++;
  }
}

int eliminate(int n) {
  int mx = 0;
  for (int i = 0; i < n + 100; ++i) tf[i] = sf[i] = 0;
  for (int i = 2; i < n; ++i) if (f[i]) {
    int p = std::upper_bound(fibs, fibs + 93, f[i]) - fibs - 1;
    assert(p >= 0);
    for (; f[i]; --p) if (f[i] >= fibs[p]) {
      f[i] -= fibs[p];
      apply(i, p);
      mx = std::max(mx, i + p + 3);
    }
  }
  for (int i = 0; i < n; ++i) {
    sf[i + 4] += sf[i];
    tf[i] += sf[i];
    f[i] = tf[i];
  }
  return mx;
}

struct Value {
  std::vector<int> u;
  int st;
  void init(int n, int m) {
    if (n > m) std::swap(n, m);
    int r = n + m + 2 - 4;
    int l = n + m + 2 - 4 * (n / 2);
    if (n % 2 == 1) {
      assert(m - n + 1 < l);
      assert(l != 2);
      if (n == m) l = 2;
      else l = m - n + 1;
      u.assign(r - l + 1, 0);
      u[0] = 1;
    } else {
      u.assign(r - l + 1, 0);
    }
    st = l;
    for (int i = 0; i < n / 2; ++i) {
      u.at(r - i * 4 - st) = 1;
    }
  }
  void add(Value &rhs) {
    if (rhs.u.empty()) return;
    if (u.empty()) {
      u.swap(rhs.u);
      std::swap(st, rhs.st);
      return;
    }
    int l = std::max(0, std::min(st, rhs.st) - 4);
    int r = std::max(st + u.size(), rhs.st + rhs.u.size()) - 1;
    if (r < 5) r = 5;
    int nt = r - l + 4;
    r += 3;
    memset(t, 0, sizeof(*t) * nt);
    for (int i = 0; i < (int)u.size(); ++i) t[i + st - l] += u[i];
    for (int i = 0; i < (int)rhs.u.size(); ++i) t[i + rhs.st - l] += rhs.u[i];
    std::reverse(t, t + nt);
    assert(t[0] == 0);
    for (int i = 0; i < nt; ++i) {
      while (i + 3 >= nt && l > 0) t[nt++] = 0, --l;
      if (i + 3 == nt) break;
      if (i + 4 == nt && t[i] == 0 && t[i + 1] == 0 && t[i + 2] == 0 && t[i + 3] == 0) break;
      if (t[i] == 0 && t[i + 1] == 2 && t[i + 2] == 0) {
        t[i] = 1; t[i + 1] = t[i + 2] = 0; t[i + 3] += 1;
      } else if (t[i] == 0 && t[i + 1] == 3 && t[i + 2] == 0) {
        t[i] = t[i + 1] = 1; t[i + 2] = 0; t[i + 3] += 1;
      } else if (t[i] == 0 && t[i + 1] == 2 && t[i + 2] == 1) {
        t[i] = t[i + 1] = 1; t[i + 2] = 0;
      } else if (t[i] == 0 && t[i + 1] == 1 && t[i + 2] == 2) {
        t[i] = t[i + 2] = 1; t[i + 1] = 0;
      }
    }
    if (l == 0) {
      t[nt - 1] = 0;
      assert(t[nt - 2] + t[nt - 3] <= 1);
      if (t[nt - 2] == 1) t[nt - 3] = 1;
      t[nt - 2] = 0;
    } else if (l == 1) {
      assert(t[nt - 1] + t[nt - 2] <= 1);
      if (t[nt - 1] == 1) t[nt - 2] = 1;
      t[nt - 1] = 0;
    }
    for (int i = 0; i < nt; ++i) assert(t[i] <= 1);
    for (int i = nt - 1; i >= 2; --i) {
      if (t[i] == 1 && t[i - 1] == 1 && t[i - 2] == 0) {
        t[i - 2] = 1; t[i] = t[i - 1] = 0;
      }
    }
    assert(t[0] == 0);
    for (int i = 0; i + 2 < nt; ++i) {
      if (t[i] == 0 && t[i + 1] == 1 && t[i + 2] == 1) {
        t[i] = 1; t[i + 1] = t[i + 2] = 0;
      }
    }
    std::reverse(t, t + nt);
    while (nt && t[nt - 1] == 0) --nt;
    if (l == 0) assert(!t[0] && !t[1]);
    if (l == 1) assert(!t[0]);
    u = {t, t + nt};
    st = l;
  }
  void print() {
    printf("%d ", st - 2 + int(u.size()));
    for (int i = 2; i < st; ++i) printf("0 ");
    for (int i = std::max(0, 2 - st); i < (int)u.size(); ++i) printf("%d ", u[i]);
    puts("");
  }
} val[N];

Value solve(int l, int r) {
  if (l + 1 == r) {
    auto u = Value(), v = Value();
    int p = std::upper_bound(fibs, fibs + 93, f[l]) - fibs - 1;
    assert(p >= 0);
    for (; f[l]; --p) if (f[l] >= fibs[p]) {
      f[l] -= fibs[p];
      v.init(l, p);
      u.add(v);
    }
    val[l] = u;
    return u;
  }
  int m = (l + r) >> 1;
  auto x = solve(l, m);
  auto y = solve(m, r);
  x.add(y);
  return x;
}

int main() {
  fibs[0] = 0; fibs[1] = 1;
  for (int i = 2; i < 93; ++i) {
    fibs[i] = fibs[i - 1] + fibs[i - 2];
  }
  mod_t zero{0}, one{1};
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d", &n); n += 2;
    for (int i = 2; i < n; ++i) scanf("%d", &a[i]);
    scanf("%d", &m); m += 2;
    for (int i = 2; i < m; ++i) scanf("%d", &b[i]);
    // conv x + y: DFT(a), DFT(b)
    // conv x - y, x \in a, y \in b, y is odd: DFT(a), DFT(rb_odd)
    // conv x - y, x \in a, y \in b, y is even: DFT(a), DFT(rb_even)
    // conv y - x, x \in a, y \in b, x is odd: DFT(b), DFT(ra_odd)
    // conv y - x, x \in a, y \in b, x is even: DFT(b), DFT(ra_even)
    for (int i = 0; i < n; ++i) {
      if (a[i]) A[i] = one;
      else A[i] = zero;
      if (i & 1) {
        RA_odd[n - 1 - i] = A[i];
        RA_even[n - 1 - i] = zero;
      } else {
        RA_even[n - 1 - i] = A[i];
        RA_odd[n - 1 - i] = zero;
      }
    }
    for (int i = 0; i < m; ++i) {
      if (b[i]) B[i] = one;
      else B[i] = zero;
      if (i & 1) {
        RB_odd[m - 1 - i] = B[i];
        RB_even[m - 1 - i] = zero;
      } else {
        RB_even[m - 1 - i] = B[i];
        RB_odd[m - 1 - i] = zero;
      }
    }

    // do conv
    const int s = n + m - 1;
    const int size = 1 << (31 - __builtin_clz(2 * s - 1));
    mod_t roots[mod_t::level], iroots[mod_t::level];
    roots[0] = mod_t::omega();
    for (int i = 1; i < mod_t::level; ++i) {
      roots[i] = roots[i - 1] * roots[i - 1];
    }
    iroots[0] = roots[0].inverse();
    for (int i = 1; i < mod_t::level; ++i) {
      iroots[i] = iroots[i - 1] * iroots[i - 1];
    }
    const auto inv = mod_t(size).inverse();
    std::fill(A + n, A + size, 0);
    std::fill(RA_odd + n, RA_odd + size, 0);
    std::fill(RA_even + n, RA_even + size, 0);
    std::fill(B + m, B + size, 0);
    std::fill(RB_odd + m, RB_odd + size, 0);
    std::fill(RB_even + m, RB_even + size, 0);
    ntt_fast::transform(A, size, roots, iroots);
    ntt_fast::transform(RA_odd, size, roots, iroots);
    ntt_fast::transform(RA_even, size, roots, iroots);
    ntt_fast::transform(B, size, roots, iroots);
    ntt_fast::transform(RB_odd, size, roots, iroots);
    ntt_fast::transform(RB_even, size, roots, iroots);
    for (int i = 0; i < size; ++i) RA_odd[i] *= B[i] * inv;
    for (int i = 0; i < size; ++i) RA_even[i] *= B[i] * inv;
    for (int i = 0; i < size; ++i) RB_odd[i] *= A[i] * inv;
    for (int i = 0; i < size; ++i) RB_even[i] *= A[i] * inv;
    for (int i = 0; i < size; ++i) A[i] *= B[i] * inv;
    ntt_fast::itransform(A, size, roots, iroots);
    ntt_fast::itransform(RA_odd, size, roots, iroots);
    ntt_fast::itransform(RA_even, size, roots, iroots);
    ntt_fast::itransform(RB_odd, size, roots, iroots);
    ntt_fast::itransform(RB_even, size, roots, iroots);

    memset(f, 0, sizeof(*f) * (s + 4));
    memset(sf, 0, sizeof(*sf) * (s + 4));
    for (int i = 0; i < s; ++i) {
      int a = A[i].get();
      int rao = RA_odd[i].get(), rae = RA_even[i].get();
      int rbo = RB_odd[i].get(), rbe = RB_even[i].get();
      if (a && i >= 2) sf[i - 2] += a;
      if (i >= m - 1 && rbe) f[i - m + 3] += rbe, sf[i - m + 3] -= rbe;
      if (i >= m - 1 && rbo) f[i - m + 5] += rbo, sf[i - m + 5] -= rbo;
      if (i >= m - 1 && rbo) f[i - m + 2] += rbo;
      if (i >= n - 1 && rae) f[i - n + 3] += rae, sf[i - n + 3] -= rae;
      if (i >= n - 1 && rao) f[i - n + 5] += rao, sf[i - n + 5] -= rao;
      if (i >= n - 1 && rao) f[i - n + 2] += rao;
    }
    for (int i = 1; i < n && i < m; i += 2) if (a[i] && b[i]) {
      f[1] -= 2, f[2] += 1;
      f[4] -= 1; sf[4] += 1;
    }
    for (int i = 0; i < n && i < m; i += 2) if (a[i] && b[i]) {
      f[2] -= 1, sf[2] += 1;
    }
    for (int i = s + 3; i >= 0; --i) {
      if (i + 4 <= s + 3) sf[i] += sf[i + 4];
      f[i] += sf[i];
      assert(f[i] >= 0);
    }
    assert(f[0] == 0 && f[1] == 0);
    // now we have to deal with carrys
    n = s + 4;
    for (int it = 0; it < 5; ++it) n = eliminate(n);
    auto ret = solve(2, n);
    ret.print();
  }
  return 0;
}
