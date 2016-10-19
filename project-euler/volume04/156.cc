#include <bits/stdc++.h>
using LL = long long;

LL f(LL n, int d) {
  LL res = 0, cnt = 0;
  for (LL len = 0, pw = 1; len < 18; pw *= 10, ++len) {
    int o = n / pw % 10;
    if (o == d) res += cnt + 1;
    res += o * (pw / 10) * len;
    res += (o > d) * pw;
    cnt += pw * o;
  }
  return res;
}

LL calc(int d) {
  const LL mx = 1ll << 60;
  LL res = 0;
  for (LL n = 1, step; n < mx; n += step) {
    LL cnt = f(n, d);
    if (cnt == n) res += n, step = 1;
    else step = n - cnt;
    if (step < 0) step = -step;
    else if (step < 8) step = 1;
    else step /= 8;
  }
  return res;
}

void run() {
  LL ret = 0;
  for (int d = 1; d <= 9; ++d) ret += calc(d);
  std::cout << ret << std::endl;
}

int main() {
  run();
  return 0;
}
