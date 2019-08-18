#include <cstdio>
#include <vector>

using int64 = long long;

int main() {
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  std::vector<int> x(b), y(b);

  auto solve = [&] (int c, int d) {
    auto at = [&](int i, int w) {
      if (y[i] >= w) return x[i] + y[i] - w;
      else return -1;
    };

    int64 ret = 0;
    std::vector<int> queue(b), l(b);
    for (int i = 0, h = 0, t = 0; i < b; ++i) {
      while (h < t && x[queue[t - 1]] <= x[i]) --t;
      queue[t++] = i;
      while (h < t && queue[h] <= i - d) ++h;
      int mx = -1;
      if (i + 1 >= d) mx = x[queue[h]];
      l[i] = mx;
    }
    for (int i = 0, h = 0, t = 0; i < b; ++i) {
      while (h < t && at(queue[t - 1], c) >= at(i, c)) --t;
      queue[t++] = i;
      while (h < t && queue[h] <= i - d) ++h;
      int mx = -1;
      if (i + 1 >= d) mx = at(queue[h], c);
      if (mx != -1 && l[i] != -1 && mx >= l[i]) {
        ret += mx - l[i] + 1;
      }
    }
    return ret;
  };

  for (int i = 0; i < b; ++i) {
    scanf("%d%d", &x[i], &y[i]);
  }

  int64 ret = solve(c, d);
  if (c != d) {
    ret += solve(d, c);
  }
  printf("%lld\n", ret);
  return 0;
}
