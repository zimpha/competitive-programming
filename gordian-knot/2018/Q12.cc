#include <cstdio>
#include <map>
#include <tuple>

int main() {
  std::map<std::tuple<int, int, int>, int> mp;
  mp[{0, 0, 1}] = 1;
  int a = 0, b = 0, c = 1;
  printf("0 0 1 ");
  for (int i = 2; i < 100; ++i) {
    int d = 4 * c - 6 * b + 4 * a;
    d %= 100;
    d += 100;
    d %= 100;
    printf("%d ", d);
    a = b, b = c, c = d;
    auto k = std::make_tuple(a, b, c);
    if (mp.count(k)) {
      //printf("extra: %d, period: %d\n", mp[k], i - mp[k]);
      //break;
    }
    mp[k] = i;
  }
  return 0;
}
