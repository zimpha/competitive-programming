#include <bits/stdc++.h>

using LL = long long;

int F(int A, int B, LL n) {
  if (n <= A + B) return n;
  std::vector<LL> f = {A, B};
  for (int i = 2; ; ++i) {
    LL x = f[i - 2] + f[i - 1];
    f.push_back(x);
    if (x >= n) break;
  }
  int s = f.size() - 1;
  while (s >= 2) {
    if (n <= f[s - 2]) s -= 2;
    else n -= f[s - 2], --s;
  }
  if (s) return n + A;
  else return n;
}

char D(std::string a, std::string b, LL n) {
  int x = F(a.size(), b.size(), n);
  if (x <= a.size()) return a[x - 1];
  else return b[x - a.size() - 1];
}

LL run() {
  const std::string A = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
  const std::string B = "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196";
  LL p7 = 1, p10 = 1, ret = 0;;
  for (int n = 0; n <= 17; ++n) {
    ret += p10 * (D(A, B, (127 + 19 * n) * p7) - '0');
    p7 *= 7;
    p10 *= 10;
  }
  return ret;
}

int main() {
  std::cout << D("1415926535", "8979323846", 35) << std::endl;
  std::cout << run() << std::endl;
  return 0;
}
