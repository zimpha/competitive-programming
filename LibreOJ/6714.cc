#include <cstdio>

int main() {
  int f[100];
  f[1] = 1;
  for (int i = 2; i < 100; ++i) {
    f[i] = 0;
    for (int d = 1; d < i; ++d) if (i % d == 0) {
      f[i] += f[d];
    }
  }
  for (int i = 1; i < 30; ++i) printf("%d, ", f[i]);
  return 0;
}
