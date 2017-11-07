#include <iostream>
#include <vector>

using int64 = long long;

int64 solve(int n) {
  std::vector<int> mp(n + 1), p;
  for (int i = 2; i <= n; ++i) {
    if (!mp[i]) p.push_back(i), mp[i] = i;
    for (int j = 0, u = n / i; j < p.size() && p[j] <= u; ++j) {
      mp[i * p[j]] = p[j];
      if (i % p[j] == 0) break;
    }
  }
  int64 ret = 0;
  for (int i = 1; i <= n; ++i) {
    int last = 0, cnt = 0, d = 1;
    bool squarefree = true;
    for (int x = i; x != 1 && d; x /= mp[x]) {
      if (mp[x] != last) {
        if (cnt == 1) d *= 2;
        else if (cnt > 2) d = 0;
        if (last) squarefree &= cnt == 1;
        last = mp[x];
        cnt = 0;
      }
      ++cnt;
    }
    if (last) squarefree &= cnt == 1;
    if (cnt == 1) d *= 2;
    else if (cnt > 2) d = 0;
    if (d % 2 == 0) d /= 2;
    ret += d;
  }
  return ret;
}

int main() {
  std::cout << solve(20000000) << std::endl;
  return 0;
}
