#include <cstdio>

const int N = 18409199 + 2, M = 100000;

bool mark[N + 1];
int twins[M], cnt;
int p[10000], m;

void prepare() {
  int last = -1;
  cnt = m = 0;
  for (int i = 2; i <= N; ++i) {
    if (!mark[i]) {
      if (i <= N / i) p[m++] = i;
      if (i - last == 2) twins[cnt++] = last;
      last = i;
    }
    for (int j = 0, u = N / i; j < m && p[j] <= u; ++j) {
      mark[p[j] * i] = 1;
      if (i % p[j] == 0) break;
    }
  }
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    printf("%d %d\n", twins[n - 1], twins[n - 1] + 2);
  }
  return 0;
}
