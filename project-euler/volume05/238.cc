#include <bits/stdc++.h>

using LL = long long;

LL run(LL upp) {
  const int M = 20300713;
  int s0 = 14025256, s = s0;
  std::vector<char> seq;
  do {
    int len = 0;
    for (int n = s; n; n /= 10) {
      seq.push_back(n % 10);
      ++len;
    }
    std::reverse(seq.end() - len, seq.end());
    s = 1ll * s * s % M;
  } while (s != s0);
  int sum = 0;
  for (auto &&x: seq) sum += x;
  std::vector<int> mx(sum + 1, -1);
  for (size_t x = 0, tot = 0; x < seq.size(); ++x) {
    int now = 0;
    for (size_t y = 0; y < seq.size(); ++y) {
      now += seq[(x + y) % seq.size()];
      if (mx[now] != -1) continue;
      mx[now] = x + 1;
      if(now) ++tot;
    }
    if (tot == sum) break;
  }
  LL ret = 0;
  for (int x = 1; x <= sum && x <= upp; ++x) {
    LL tot = (upp - x) / sum + 1;
    ret += mx[x] * tot;
  }
  return ret;
}

int main() {
  std::cout << run(1000) << std::endl;
  std::cout << run(2000000000000000ll) << std::endl;
  return 0;
}
