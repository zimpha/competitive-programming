#include <cstdio>
#include <cstring>

const int N = (1 << 21) + 10;

int sj[N], si[N], so[N], f[N], g[N];
char s[N];

int main() {
  int k;
  scanf("%d%s", &k, s);
  int n = 1 << (k * 2);
  for (int i = 0; i < n * 2; ++i) {
    if (i) sj[i] = sj[i - 1], si[i] = si[i - 1], so[i] = so[i - 1];
    sj[i] += s[i % n] == 'J';
    so[i] += s[i % n] == 'O';
    si[i] += s[i % n] == 'I';
  }
  for (int j = 1; j <= k; ++j) {
    int l = 1 << (j * 2 - 2);
    for (int i = 0; i < n; ++i) {
      g[i] = l * 3 - (sj[i + l - 1] - (i ? sj[i - 1] : 0)) - (so[i + l * 2 - 1] - so[i + l - 1]) - (si[i + l * 3 - 1] - si[i + l * 2 - 1]) + f[(i + l * 3) % n];
      //printf("i=%d J=%d O=%d I=%d\n", i, (sj[i + l - 1] - (i ? sj[i - 1] : 0)), (so[i + l * 2 - 1] - so[i + l - 1]), (si[i + l * 3 - 1] - si[i + l * 2 - 1]));
    }
    memcpy(f, g, sizeof(g[0]) * n);
  }
  int ret = -1;
  for (int i = 0; i < n; ++i) {
    if (ret == -1 || f[i] < ret) ret = f[i];
  }
  printf("%d\n", ret);
  return 0;
}
