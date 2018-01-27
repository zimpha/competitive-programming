#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <stack>
#include <queue>

#include <tuple>

#define getchar getchar_unlocked
#define putchar putchar_unlocked

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

int get_int() {
  int c, n;
  while ((c = getchar()) < '0');
  n = c - '0';
  while ((c = getchar()) >= '0') n = n * 10 + (c - '0');
  return n;
}

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

  template <typename word>
    word gcd(word a, word b) {
      while (b) { word t = a % b; a = b; b = t; }
      return a;
    }

  template <typename word, typename mod>
    word brent(word n, word c) {
      // n must be composite and odd.
      const u64 s = 256;
      mod::set_mod(n);
      const mod one = mod(1), mc = mod(c);
      auto f = [&] (mod x) { return x * x + mc; };
      mod y = one;
      for (u64 l = 1; ; l <<= 1) {
        auto x = y;
        rep(_, l) y = f(y);
        mod p = one;
        rep(k, 0, l, s) {
          auto sy = y;
          rep(_, min(s, l - k)) y = f(y), p *= y - x;
          word g = gcd(n, p.n_);
          if (g == 1) continue;
          if (g == n) for (g = 1, y = sy; g == 1; ) y = f(y), g = gcd(n, (y - x).n_);
          return g;
        }
      }
    }

  u64 brent(u64 n, u64 c) {
    if (n < (u32(1) << 31)) {
      return brent<u32, m32>(n, c);
    } else if (n < (u64(1) << 63)) {
      return brent<u64, m64>(n, c);
    } else {
      assert(0);
    }
  }

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

  u32 isqrt(u64 n) {
    return sqrtl(n);
  }

  u64 square(u64 n) {
    return n * n;
  }

  u64 ctz(u64 n) {
    return __builtin_ctzll(n);
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

  bool is_prime_power_2(u64 n) {
    if (n <= 1) return false;
    if (!(n & 1)) return (n & (n - 1)) == 0;
    const u32 bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (u64 q = n; ; ) {
      int s = __builtin_ctzll(q - 1);
      u64 d = (q - 1) >> s;
      u32 a = composite<u64, m64>(q, d, s, bases, 7);
      if (a % q == 0) {
        while (n % q == 0) n /= q;
        return n == 1;
      }
      m64 b = a;
      u64 g = gcd((b.pow(q) - b).val(), q);
      if (g == 1 || g == q) return false;
      q = g;
    }
  }

  u128 ipow(u128 a, int e) {
    u128 ret = 1;
    for (; e; e >>= 1, a = a * a) {
      if (e & 1) ret *= a;
    }
    return ret;
  }

  pair<u64, bool> kth_integer_root(u64 n, int k) {
    if (k == 1) return {n, true};
    if (k == 2) {
      u64 ret = sqrtl(n);
      return {ret, ret * ret == n};
    }
    if (k == 3) {
      u32 ret = cbrtl(n);
      return {ret, u64(ret) * ret * ret == n};
    }
    u64 ret = pow(n, 1. / k);
    while (ipow(ret, k) < n) ++ret;
    u128 a = 0;
    while ((a = ipow(ret, k)) > n) --ret;
    return {ret, a == n};
  }

  bool is_prime_power(u64 n) {
    if (n <= 1) return false;
    if (!(n & 1)) return (n & (n - 1)) == 0;
    rep(i, 1, primes.size()) {
      auto p = primes[i];
      if (square(p.n) > n) return true;
      if (!p.divide(n)) continue;
      while (p.divide(n)) n = n / p;
      return n == 1;
    }
    static const int ps[] = {
      2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
      31, 37, 41, 43, 47, 53, 59, 61
    };
    rep(i, 18) {
      for (int k = ps[i]; ;) {
        u64 a; bool exact;
        tie(a, exact) = kth_integer_root(n, k);
        if (a <= primes.back().n) return miller_rabin(n);
        if (!exact) break;
        n = a;
      }
    }
    assert(0);
  }

  using P = pair<u64, u32>;
  vector<P> factors(u64 n) {
    assert(n < (u64(1) << 63));

    auto ret = vector<P>();
    if (n <= 1) {
      return ret;
    }

    u32 v = isqrt(n);
    if (u64(v) * v == n) {
      auto res = factors(v);
      for (auto& pe : res) pe.second <<= 1;
      return res;
    }

    if (!(n & 1)) {
      u32 e = ctz(n);
      ret.emplace_back(2, e);
      n >>= e;
    }

    u64 lim = square(primes[primes.size() - 1].n);
    rep(pi, 1, primes.size()) {
      auto p = primes[pi];
      if (square(p.n) > n) break;
      if (p.divide(n)) {
        u32 e = 1; n = n / p;
        while (p.divide(n)) n = n / p, e++;
        ret.emplace_back(p.n, e);
      }
    }

    u32 s = ret.size();
    while (n > lim && !miller_rabin(n)) { 
      for (u64 c = 1; ; ++c) {
        u64 p = brent(n, c);
        if (!miller_rabin(p)) continue;
        u32 e = 1; n /= p;
        while (n % p == 0) n /= p, e += 1;
        ret.emplace_back(p, e);
        break;
      }
    }
    if (n > 1) ret.emplace_back(n, 1);
    if (ret.size() - s >= 2) sort(ret.begin() + s, ret.end());
    return ret;
  }

} // namespace factor

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int MM = 1e9 + 7;
const double eps = 1e-8;
const int MAXN = 2e6 + 10;

int n, m;

void prework(){

}

void read(){

}

void solve(int n){
  //	cout << "Case #" << casi << ": ";
  int ans = 0;
  int x, y, z;
  for (int p = 1; p <= n; p++)
    for (int q = p + 1; q <= n; q++) if (p + q <= n)
      for (int r = q + 1; r <= n; r++) if (p + q + r <= n){
        int now = __gcd(__gcd(p*q+1, p*r+1), q*r+1);
        if (now > ans){
          ans = now;
          x=p,y=q,z=r;
        }
      }else break;
  else break;
  cout << n << ' ' << ans << ' ' << x << ' ' << y << ' ' << z << endl;
}

void printans(){

}


class Primality {
  public:
    typedef long long LL;
    // 判断num是否为质数
    bool miller_rabin(LL num){
      if(num<=1) return false;
      if(num<=3) return true;
      if(~num&1) return false;
      const int u[]={2,325,9375,28178,450775,9780504,1795265022,0};
      //const int u[]={2,3,5,7,11,13,17,19,23,29,0};
      LL e=num-1,a,c=0;
      while(~e&1) e/=2,c++;
      for(int i=0;u[i];i++){
        if(num<=u[i]) return true;
        a=POW(u[i],e,num);
        if(a==1) continue;
        for(int j=1;a!=num-1;j++){
          if(j==c) return false;
          a=MUL(a,a,num);
        }
      }
      return true;
    }
    // 求一个小于n的因数，期望复杂度为O(n^0.25)，当n为非合数时返回n本身
    LL pollard_rho(LL n){
      if(n<=3 || miller_rabin(n)) return n; // 保证n为合数时可去掉这行
      while(1){
        int i=1,cnt=2;
        LL x=rand()%n,y=x,c=rand()%n;
        if(!c || c==n-2) c++;
        do{
          LL u=__gcd(n-x+y,n);
          if(u>1 && u<n) return u;
          if(++i==cnt) y=x,cnt*=2;
          x=(c+MUL(x,x,n))%n;
        }while(x!=y);
      }
      return n;
    }
    // 使用rho方法对n做质因数分解，建议先筛去小质因数后再用此函数
    vector<LL> factorize(LL n){
      vector<LL> u;
      if(n>1) u.push_back(n);
      for(size_t i=0;i<u.size();i++){
        LL x=pollard_rho(u[i]);
        if(x==u[i]) continue;
        u[i--]/=x;
        u.push_back(x);
      }
      sort(u.begin(),u.end());
      return u;
    }
    // 返回x与y相乘模m的结果，x与m要小于2^62
    LL MUL(LL a, LL b, LL mod) {//O(1) long long 乘法
      assert(0 <= a && a < mod);
      assert(0 <= b && b < mod);
      if (mod < int(1e9)) return a * b % mod;
      LL k = (LL)((long double)a * b / mod);
      LL res = a * b - k * mod;
      res %= mod;
      if (res < 0) res += mod;
      return res;
    }
    /*普通的快速乘
      LL MUL(LL x, LL y, LL m){
      LL c,s=0;
      for(c=x%m;y;c=(c+c)%m,y>>=1)
      if(y&1) s=(s+c)%m;
      return s;
      }*/
    // 返回x的y次方模m的结果，x与m要小于2^62
    LL POW(LL x, LL y, LL m){
      LL c,s=1;
      for(c=x%m;y;c=MUL(c,c,m),y>>=1)
        if(y&1) s=MUL(s,c,m);
      return s;
    }
} nico;

int main(){

  factor::init(512);
  int n = 667788990;
  n = n / 3 * 3;
  ll ans = 0;//222533369;
  for (int i = 1; i <= 10000001; i++){
    ll q = n / 3;
    ll rst = q * q + 1;
    auto factors = factor::factors(rst);
    ll mx = 0;
    std::function<void(int, u64)> rec = [&](int d, u64 now) {
      mx = std::max<u64>(mx, now);
      for (int i = d; i < factors.size(); ++i) {
        u64 p = factors[i].first;
        int ue = factors[i].second;
        u64 t_now = now;
        for (int e = 0; e < ue; ++e) {
          t_now *= p;
          if (t_now >= q) break;
          rec(i + 1, t_now);
        }
      }
    };
    if (q > 1) rec(0, 1);
    /*
       if (q % 2 == 1 && mx % 2 == 0 && rst % (2 * mx) == mx) {
       if (mx * 2 > ans) {
       ans = mx * 2;
       cout << q << ' ' << ans << endl;
       }
       } else {
       if (mx > ans) {
       ans = mx;
       cout << q << ' ' << ans << endl;
       }
       }*/
    if (mx > ans) {
      ans = mx;
      cout << q << ' ' << ans << endl;
    }
    //if (i % 10000 == 0) cout << ans << endl;
    n -= 3;
  }
  cout << ans << endl;

  //for (int i = 6; i <= 1000; i++) solve(i);
  return 0;
}
