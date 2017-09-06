#include <cstdio>
#include <array>
#include <vector>

using point = std::array<int, 5>;

int operator * (const point &a, const point &b) {
  int ret = 0;
  for (int i = 0; i < 5; ++i) {
    ret += a[i] * b[i];
  }
  return ret;
}

point operator - (const point &a, const point &b) {
  point c;
  for (int i = 0; i < 5; ++i) {
    c[i] = a[i] - b[i];
  }
  return std::move(c);
}

int main() {
  int n;
  scanf("%d", &n);
  if (n > 20) {
    puts("0");
    return 0;
  }
  std::vector<point> p(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 5; ++j) {
      scanf("%d", &p[i][j]);
    }
  }
  std::vector<int> res;
  for (int a = 0; a < n; ++a) {
    bool good = true;
    for (int b = 0; b < n && good; ++b) {
      for (int c = 0; c < n && good; ++c) {
        if (a == b || b == c || c == a) continue;
        if ((p[b] - p[a]) * (p[c] - p[a]) > 0) good = false;
      }
    }
    if (good) res.push_back(a);
  }
  printf("%d\n", (int)res.size());
  for (auto &&e: res) printf("%d ", e + 1);
  puts("");
  return 0;
}