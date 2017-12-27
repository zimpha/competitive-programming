#include <cstdio>
#include <algorithm>
#include <vector>

using int64 = long long;

const int M = 1000 + 10;

struct tri_t {
	int x, y, m;
};

int main() {
  int n;
  scanf("%d", &n);
  std::vector<tri_t> tri(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%d", &tri[i].x, &tri[i].y, &tri[i].m);
  }
  std::sort(tri.begin(), tri.end(), [](const tri_t &a, const tri_t &b) {
      return a.y < b.y;
  });
  std::vector<int> event(n + 1);
  for (int i = 0; i < n; ++i) {
    event[i] = tri[i].x;
  }
  event.back() = 1e8;
  std::sort(event.begin(), event.end());
  std::vector<int64> area(M);
  for (int i = 0; i < M; ++i) area[i] = i * i;
  auto trapeces_area = [&] (int x1, int x2, int x3) {
	  if (x3 <= x2) return area[x3 - x1];
    else return area[x3 - x1] - area[x3 - x2];
  };
  int64 ret = 0;
  for (int i = 1; i <= n; ++i) if (event[i] > event[i - 1]) {
    int prevX = event[i - 1], prevY = 0;
    for (int j = 0; j < n; ++j) {
      if (tri[j].x <= event[i - 1] && tri[j].x + tri[j].m > event[i - 1]) {
        if (prevX > event[i - 1]) {
          prevX -= tri[j].y - prevY;
          prevY = tri[j].y;
        }
        if (tri[j].x + tri[j].m > prevX) {
          ret += trapeces_area(event[i - 1], event[i], tri[j].x + tri[j].m);
          if (prevX > event[i - 1]) {
            ret -= trapeces_area(event[i - 1], event[i], prevX);
          }
          prevX = tri[j].x + tri[j].m;
          prevY = tri[j].y;
        }
      }
    }
  }
  if (ret % 2) printf("%lld.5\n", ret / 2);
  else printf("%lld.0\n", ret / 2);
  return 0;
}
