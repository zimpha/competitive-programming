#include <bits/stdc++.h>

using LL = long long;

void exgcd(LL a, LL b, LL &g, LL &x, LL &y) {
  if (!b) x = 1, y = 0, g = a;
  else {
    exgcd(b, a % b, g, y, x);
    y -= x * (a / b);
  }
}


//ax + by = c,x >= 0, x is minimum
//xx = x + t * b, yy = y - t * a
bool linear_equation(LL a, LL b, LL c, LL &x, LL &y) {
  LL g;
  exgcd(a,b,g,x,y);
  if (g < 0) g = -g, x = -x, y = -y;
  if (c % g) return false;
  b /= g, a /= g, c /= g;
  x = x * c % b;
  y = (c - a * x) / b;
  return true;
}

void run() {
  LL a1, b1, a2, b2, L, R;
  std::cin >> a1 >> b1 >> a2 >> b2 >> L >> R;
  LL x, y, ret = 0;
  if (!linear_equation(a1, -a2, b2 - b1, x, y)) {
    ret = 0;
  } else {
    L = std::max(L, std::max(b1, b2));
    LL res = a1 * x + b1;
    LL lcm = a1 * a2 / std::__gcd(a1, a2);
    if (res < R) res += (R - res) / lcm * lcm;
    if (res > R) res -= (res - R + lcm - 1) / lcm * lcm;
    ret = res >= L ? (res - L) / lcm + 1 : 0;
  }
  std::cout << ret << std::endl;
}

int main() {
  run();
  return 0;
}
