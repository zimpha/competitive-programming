#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>

using int64 = long long;

bool is_pandigital(int64 n) {
  static bool mark[10];
  memset(mark, 0, sizeof(mark));
  int cnt = 0;
  while (n) {
    if (mark[n % 10]) return false;
    mark[n % 10] = true;
    n /= 10;
    ++cnt;
  }
  return cnt == 5 || cnt == 10;
}

int main() {
  int64 cnt = 0, sum = 0;
  std::vector<int64> candidate;
  for (int64 i = 10000; i <= 99999; ++i) {
    if (is_pandigital(i) && is_pandigital(i * i)) candidate.push_back(i);
  }
  for (auto &&x: candidate) {
    for (auto &&y: candidate) {
      if (is_pandigital(x * 100000 + y)) {
        ++cnt;
        sum += x * 100000 + y;
      }
    }
  }
  printf("%lld,%lld\n", cnt, sum);
  return 0;
}
