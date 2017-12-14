#include <cstdio>
#include <algorithm>

using int64 = long long;
const int N = 1e5 + 10;

int64 mu[N], sd[N];

void prepare() {
  for (int i = 1; i < N; ++i) {
    mu[i] += i == 1;
    sd[i] += 1;
    for (int j = i + i; j < N; j += i) {
      mu[j] -= mu[i];
      sd[j] += 1;
    }
    mu[i] += mu[i - 1];
    sd[i] += sd[i - 1];
  }
}

int main() {
  prepare();
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, m;
    scanf("%d%d", &n, &m);
    int64 ret = 0;
    for (int i = 1, j; i <= n && i <= m; i = j + 1) {
      j = std::min(n / (n / i), m / (m / i));
      ret += (mu[j] - mu[i - 1]) * sd[n / i] * sd[m / i];
    }
    printf("%lld\n", ret);
  }
  return 0;
}
