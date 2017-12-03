#include <cstdio>
#include <cmath>

using ll = long long;

ll pow_mod(ll a, ll n, ll m) {
  ll r = 1;
  for (; n; n >>= 1) {
    if (n & 1) r = r * a % m;
    a = a * a % m;
  }
  return r;
}

double solve(int n, int r) {
  double sum = 0;
  for (int k = 0; k <= n; ++k) {
    sum += 1.0 * pow_mod(16, n - k, k * 8 + r) / (k * 8 + r);
  }
  return sum;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    --n;
    double sum = 4 * solve(n, 1) - 2 * solve(n, 4) - solve(n, 5) - solve(n, 6);
    sum = fabs(sum - (int)sum + 1);
    const char base[] = "0123456789ABCDEF";
    if (n < 0) putchar('3');
    else putchar(base[int((sum - floor(sum)) * 16)]);
  }
  puts("");
  return 0;
}
