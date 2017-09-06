#include <cstdio>

using int64 = long long;

int64 dis(int64 x1, int64 y1, int64 x2, int64 y2) {
  return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

bool coline(int64 x1, int64 y1, int64 x2, int64 y2, int64 x3, int64 y3) {
  return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1) == 0;
}

int main() {
  int64 x1, y1, x2, y2, x3, y3;
  scanf("%lld%lld%lld%lld%lld%lld", &x1, &y1, &x2, &y2, &x3, &y3);
  if (coline(x1, y1, x2, y2, x3, y3) || dis(x1, y1, x2, y2) != dis(x2, y2, x3, y3)) {
    puts("No");
  } else {
    puts("Yes");
  }
  return 0;
}