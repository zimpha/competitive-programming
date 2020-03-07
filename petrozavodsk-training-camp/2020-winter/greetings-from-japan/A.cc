#include <cstdio>
#include <algorithm>

using int64 = long long;

int solve(int64 t) {
  int64 ret = t;
  int64 sum = 1;
  int step = 1;
  // 1, 3, ..., p, p/3, .., 3
  for (int64 p = 3; ; p *= 3) {
    if (sum * 2 + p - 1 > t) break;
    auto rest = t - sum * 2 - p + 1;
    int64 now = step * 2;
    for (auto m = p; rest; m /= 3) {
      now += rest / m;
      rest -= rest / m * m;
    }
    if (now < ret) ret = now;
    ++step;
    sum += p;
  }
  return ret;
}

int main() {
  int64 t;
  scanf("%lld", &t);
  printf("%d\n", solve(t));
  return 0;
}
