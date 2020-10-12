#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using i64 = long long;

std::map<i64, i64> cache;

i64 query(i64 x) {
  if (cache.count(x)) {
    return cache[x];
  }
  printf("read %lld\n", x);
  fflush(stdout);
  scanf("%lld", &cache[x]);
  return cache[x];
}

bool check(i64 n) {
  i64 x = 0;
  for (int it = 0; it < 25000 && x < n; ++it) {
    i64 v = query(x);
    i64 xx = x + v + 1;
    if (xx >= n) return false;
    if (query(xx) != v) return false;
    x = xx + 1;
  }
  return x == n;
}

int main() {
  i64 n;
  scanf("%lld", &n);
  i64 x = 0;
  std::vector<i64> px;
  for (int it = 0; it < 25000 && x < n; ++it) {
    i64 v = query(x);
    i64 xx = x + v + 1;
    px.push_back(x);
    px.push_back(xx);
    x = xx + 1;
  }
  i64 y = n - 1;
  std::vector<i64> py;
  for (int it = 0; it < 25000 && y >= 0; ++it) {
    i64 v = query(y);
    i64 yy = y - v - 1;
    py.push_back(y);
    py.push_back(yy);
    y = yy - 1;
  }
  std::reverse(py.begin(), py.end());
  //for (auto &x: px) printf("%lld ", x); puts("");
  //for (auto &x: py) printf("%lld ", x); puts("");
  if (x == n && y == -1 && px == py) {
    puts("fix 0"); 
    return 0;
  }
  if (x == n) {
    for (size_t i = 0; i < px.size() && i < py.size(); i += 2) {
      i64 x2 = px[px.size() - i - 1], x1 = px[px.size() - i - 2];
      i64 y2 = py[py.size() - i - 1], y1 = py[py.size() - i - 2];
      if (x2 == y2 && x1 == y1) continue;
      //printf("x1=%lld x2=%lld y1=%lld y2=%lld\n", x1, x2, y1, y2);
      i64 w = query(y2);
      cache[y2] = x2 - x1 - 1;
      if (check(n)) {
        puts("fix 1");
        printf("%lld %lld\n", y2, x2 - x1 - 1);
        return 0;
      }
      cache[y2] = w;
      break;
    }
  }
  if (y == -1) {
    for (size_t i = 0; i < px.size() && i < py.size(); i += 2) {
      i64 x2 = px[i + 1], x1 = px[i];
      i64 y2 = py[i + 1], y1 = py[i];
      if (x2 == y2 && x1 == y1) continue;
      //printf("x1=%lld x2=%lld y1=%lld y2=%lld\n", x1, x2, y1, y2);
      i64 w = query(x1);
      cache[x1] = y2 - y1 - 1;
      if (check(n)) {
        puts("fix 1");
        printf("%lld %lld\n", x1, y2 - y1 - 1);
        return 0;
      }
      cache[x1] = w;
      break;
    }
  }
  puts("fix 2");
  printf("0 %lld\n", n - 2);
  printf("%lld %lld\n", n - 1, n - 2);
  return 0;
}
