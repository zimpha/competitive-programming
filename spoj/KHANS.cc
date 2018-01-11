#include <cstdio>

using int64 = long long;

int next(int x) {
  int r = x & -x;
  x += r;
  if (!x) return -1;
  int z = x & -x;
  z -= r;
  while (!(z & 1)) z >>= 1;
  return x | (z >> 1);
}

int prev(int x) {
  x = next(~x);
  if (x == -1) return -1;
  if (x) x = ~x;
  return x;
}

int main() {
  int n;
  scanf("%d", &n);
  int64 cnt = 0, sum = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    int a = prev(x), b = next(x);
    if ((int64)x * x == (int64)a * b) ++cnt;
    sum += b - a;
  }
  printf("%.10f %.10f\n", 1.0 * cnt / n, 1.0 * sum / n);
  return 0;
}
