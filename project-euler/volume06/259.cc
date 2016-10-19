#include <bits/stdc++.h>
typedef long long LL;

template<typename T>
struct fraction {
  T a, b;
  fraction(): a(0), b(1) {}
  fraction(T a, T b):a(a), b(b) {fix();}
  void fix() {
    if (b == 0) a = 1;
    T g = std::__gcd(abs(a), abs(b));
    a /= g, b /= g;
    if (b < 0) a = -a, b = -b;
  }
  bool operator == (const fraction &r) const {
    return a * r.b == b * r.a;
  }
  bool operator < (const fraction &r) const {
    return a * r.b < b * r.a;
  }
  bool operator <= (const fraction &r) const {
    return a * r.b <= b * r.a;
  }
  fraction operator + (const fraction &r) const {
    return fraction(a * r.b + b * r.a, b * r.b);
  }
  fraction operator + (const T x) const {
    return fraction(a + b * x, b);
  }
  fraction operator - (const fraction &r) const {
    return fraction(a * r.b - b * r.a, b * r.b);
  }
  fraction operator - (const T x) const {
    return fraction(a - b * x, b);
  }
  fraction operator * (const fraction &r) const {
    return fraction(a * r.a, b * r.b);
  }
  fraction operator * (const T x) const {
    return fraction(a * x, b);
  }
  fraction operator / (const fraction &r) const {
    return fraction(a * r.b, b * r.a);
  }
  fraction operator / (const T x) const {
    return fraction(a, b * x);
  }
  fraction& operator += (const fraction &r) {
    a = a * r.b + b * r.a;
    b *= r.b;
    fix();
    return *this;
  }
  fraction& operator += (const T x) {
    a += b * x;
    fix();
    return *this;
  }
  fraction& operator -= (const fraction &r) {
    a = a * r.b - b * r.a;
    b *= r.b;
    fix();
    return *this;
  }
  fraction& operator -= (const T x) {
    a -= b * x;
    fix();
    return *this;
  }
  fraction& operator *= (const fraction &r) {
    a *= r.a;
    b *= r.b;
    fix();
    return *this;
  }
  fraction& operator *= (const T x) {
    a *= x;
    fix();
    return *this;
  }
  fraction& operator /= (const fraction &r) {
    a *= r.b; b *= r.a;
    fix();
    return *this;
  }
  fraction& operator /= (const T x) {
    b *= x;
    fix();
    return *this;
  }
};

std::set<fraction<LL>> dp[10][10];

void solve(int l, int r) {
  if (dp[l][r].size()) return;
  int val = 0;
  for (int i = l; i <= r; ++i) val = val * 10 + i;
  dp[l][r].insert(fraction<LL>(val, 1));
  if (l == r) return;
  for (int i = l; i < r; ++i) {
    solve(l, i);
    solve(i + 1, r);
    for (auto &x: dp[l][i]) {
      for (auto &y: dp[i + 1][r]) {
        dp[l][r].insert(x + y);
        dp[l][r].insert(x - y);
        dp[l][r].insert(x * y);
        dp[l][r].insert(x / y);
      }
    }
  }
}

LL run() {
  solve(1, 9);
  LL ret = 0;
  for (auto &&x: dp[1][9]) {
    if (x.b == 1 && x.a > 0) ret += x.a;
  }
  return ret;
}

int main() {
  std::cout << run() << std::endl;
  return 0;
}
