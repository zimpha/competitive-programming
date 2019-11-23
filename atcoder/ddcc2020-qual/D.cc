#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> s;
  int64 ret = 0;
  for (int i = 0; i < n; ++i) {
    int64 d, c;
    scanf("%lld%lld", &d, &c);
    for (; c > 1; c >>= 1) {
      if (c & 1) s.push_back(d);
      if (d + d > 9) ret += c / 2 * 2;
      else ret += c / 2;
      if (d != 0 && d != 9) d = d * 2 % 9;
    }
    s.push_back(d);
  }
  while (s.size() > 1) {
    int a = s.back(); s.pop_back();
    int b = s.back(); s.pop_back();
    int c = a + b;
    if (c > 9) ret += 2, c = c % 10 + c / 10;
    else ++ret;
    s.push_back(c);
  }
  printf("%lld\n", ret);
  return 0;
}
