#include <cstdio>
#include <algorithm>

using int64 = long long;

const int N = 3000 + 10;

int64 sqr(int64 x) { return x * x; }

bool removed[N];
std::pair<int, int> p[N], q[N];

void output(double x, double y, double len) {
  printf("%.3f %.3f %.3f %.3f\n", x - len, y - len, x, y);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &p[i].first, &p[i].second);
  }
  std::sort(p, p + n);
  puts("Yes");
  while (n) {
    int m = 0;
    for (int i = 0; i < n; ++i) {
      if (!removed[i]) q[m++] = p[i];
    }
    n = m;
    if (n == 0) break;
    for (int i = 0; i < n; ++i) p[i] = q[i];
    for (int i = 0; i < n; ++i) removed[i] = 0;
    if (p[0].first == p[1].first) {
      removed[0] = removed[1] = 1;
      output(p[1].first, p[1].second, p[1].second - p[0].second);
      continue;
    }
    if (p[1].second >= p[0].second) {
      removed[0] = removed[1] = 1;
      output(p[1].first, p[1].second, std::max(p[1].second - p[0].second, p[1].first - p[0].first));
      continue;
    }
    if (n == 2 || p[2].first != p[1].first) {
      removed[0] = removed[1] = 1;
      output(p[1].first, p[0].second, std::max(p[0].second - p[1].second, p[1].first - p[0].first));
      continue;
    }
    if (p[2].second < p[0].second) {
      removed[1] = removed[2] = 1;
      output(p[2].first, p[2].second, p[2].second - p[1].second);
      continue;
    }
    if (p[2].second > p[0].second) {
      removed[0] = removed[1] = 1;
      output(p[1].first, p[0].second, std::max(p[0].second - p[1].second, p[1].first - p[0].first));
      continue;
    }
    int dx = p[2].first - p[0].first;
    int dy = p[2].second - p[1].second;
    if (dx < dy) {
      removed[0] = removed[2] = 1;
      output(p[2].first, p[2].second, dx);
    } else if (dx > dy) {
      removed[1] = removed[2] = 1;
      output(p[2].first, p[2].second, dy);
    } else {
      removed[1] = removed[2] = 1;
      output(p[2].first + 0.5, p[2].second, dy);
    }
  }
  return 0;
}
