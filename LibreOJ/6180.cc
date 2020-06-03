#include <cstdio>

struct FastIO {
  static const int S = 65536;
  char buf[S];
  int pos, len;
  bool eof;
  FILE *in;
  FastIO(FILE *_in = stdin) {
    in = _in;
    pos = len = 0;
    eof = false;
  }
  inline int nextChar() {
    if (pos == len)
      pos = 0, len = fread(buf, 1, S, in);
    if (pos == len) {eof = true; return -1;}
    return buf[pos++];
  }
  inline int nextUInt() {
    int c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    for (;'0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x;
  }
  inline int nextInt() {
    int s = 1, c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    if (c == '-') s = -1, c = nextChar();
    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x * s;
  }
  inline int nextString(char *s) {
    auto p = s;
    int c = nextChar();
    while (c <= 32) c = nextChar();
    for(; c > 32; c = nextChar()) *s++ = c;
    *s = 0;
    return s - p;
  }
} io;

using uint32 = unsigned int;
using uint64 = unsigned long long;

// Montgomery modular multiplication -- about 7x faster
// ensure mod is an odd number, use after call `set_mod` method
struct UnsafeMod {
  using word = uint32;
  using dword = uint64;
  using sword = int;
  UnsafeMod(): x(0) {}
  UnsafeMod(word _x): x(init(_x)) {}

  bool operator == (const UnsafeMod& rhs) const {
    return x == rhs.x;
  }
  bool operator != (const UnsafeMod& rhs) const {
    return x != rhs.x;
  }
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
  word get() const {
    return reduce(x);
  }

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

  static constexpr int word_bits = sizeof(word) * 8;
  static constexpr word mod = 998244353;
  static constexpr word inv = 3296722945;
  static constexpr word r2 = 932051910;

  word x;
};

const int N = 1e5 + 10;
const int mod = 998244353;

char s[N];

int main() {
  uint64 n = 0;
  int len = io.nextString(s);
  int k = 1 << io.nextUInt();
  for (int i = 0; i < len; ++i) {
    n = (n * 10 + s[i] - '0') % (mod - 1);
  }
  auto g = UnsafeMod(3).pow((mod - 1) / k);
  auto p = UnsafeMod(1);
  auto ret = UnsafeMod(0);
  for (int i = 0; i < k; ++i) {
    ret += (p + 1).pow(n);
    p *= g;
  }
  ret *= UnsafeMod(k).pow(mod - 2);
  printf("%u\n", ret.get());
  return 0;
}
