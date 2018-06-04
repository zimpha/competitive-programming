#include <cstdio>
#include <map>

const int N = 1e7 + 10;

using int64 = long long;

int mem[N];

int main() {
  for (int i = N - 1; i >= 1; --i) {
    int64 ret = 1;
    for (int j = 1; j <= i; ++j) {
      ret *= (i - j + 1);
      ret /= j;
      if (ret >= N) break;
      mem[ret] = i;
    }
  }
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int S;
    scanf("%d", &S);
    int ret = S + 1;
    for (int i = 1; i * i <= S; ++i) if (S % i == 0) {
      ret = std::min(ret, mem[i] + mem[S / i]);
    }
    printf("Case #%d: %d\n", cas, ret);
  }
  return 0;
}
