#include <bits/stdc++.h>

using LL = long long;

int main() {
  const int A[] = {5248, 1312, 2624, 5760, 3936};
  const int B[] = {640, 1888, 3776, 3776, 5664};
  const int SA = 18880, SB = 15744;
  static LL va[50000000], vb[50000000];
  std::vector<std::pair<int, int>> S[5];
  std::set<std::pair<int, int>> res;
  for (int x = 1; x <= A[0]; ++x) {
    for (int y = 1; y <= B[0]; ++y) {
      LL a = x * B[0], b = y * A[0];
      LL g = std::__gcd(a, b);
      a /= g, b /= g;
      if (res.count({a, b}) || a >= b) continue;
      for (int i = 1; i < 5; ++i) {
        S[i].clear();
        LL u = a * A[i], v = b * B[i];
        LL g = std::__gcd(u, v);
        u /= g, v /= g;
        for (int k = 1; ; ++k) {
          if (k * u <= A[i] && k * v <= B[i]) S[i].push_back({k * u, k * v});
          else break;
        }
      }
      LL u = a * SB, v = b * SA;
      std::swap(u, v);
      int ma = 0, mb = 0;
      for (auto &&e: S[1]) {
        for (auto &&f: S[2]) {
          int sx = e.first + f.first, sy = e.second + f.second;
          va[ma++] = v * x + v * sx - u * sy;
        }
      }
      for (auto &&e: S[3]) {
        for (auto &&f: S[4]) {
          int sx = e.first + f.first, sy = e.second + f.second;
          vb[mb++] = u * y + u * sy - v * sx;
        }
      }
      std::sort(va, va + ma);
      std::sort(vb, vb + mb);
      bool flag = false;
      for (int i = 0, j = 0; i < ma && j < mb && !flag; ) {
        if (va[i] < vb[j]) ++i;
        else if (va[i] > vb[j]) ++j;
        else flag = true;
      }
      if (flag) {
        res.insert({a, b});
        std::cout << a << ' ' << b << std::endl;
      }
    }
  }
  std::cout << res.size() << std::endl;
  auto ret = *res.begin();
  for (auto &&e: res) {
    if (ret.second * e.first < ret.first * e.second) ret = e;
  }
  std::cout << ret.second << '/' << ret.first << std::endl;
  return 0;
}
