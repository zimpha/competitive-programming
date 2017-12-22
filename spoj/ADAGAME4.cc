#include <cstdio>
#include <set>
#include <vector>

const int N = 2e7, M = 1000;

int d[N + 1], e[N + 1], p[M], m;

void prepare() {
  d[1] = 1;
  for (int i = 2; i <= N; ++i) {
    if (!d[i]) {
      d[i] = 2;
      e[i] = 2;
      if (i <= N / i) p[m++] = i;
    }
    for (int j = 0, u = N / i; j < m && p[j] <= u; ++j) {
      int v = i * p[j];
      if (i % p[j]) {
        e[v] = 2;
        d[v] = d[i] * e[v];
      } else {
        e[v] = e[i] + 1;
        d[v] = d[i] / e[i] * e[v];
        break;
      }
    }
  }
}

int main() {
  prepare();
  e[0] = 0;
  for (int i = 1; i <= N; ++i) {
    unsigned int mark = 0;
    for (int j = 1; j <= d[i]; ++j) {
      if (e[i - j] <= 31) mark |= 1u << e[i - j];
    }
    e[i] = __builtin_ctz(~mark);
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    puts(e[n] ? "Ada" : "Vinit");
  }
  return 0;
}
