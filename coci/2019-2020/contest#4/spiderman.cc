#include <cstdio>

const int N = 1e6 + 10;

int cnt[N], ret[N], h[N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
    cnt[h[i]]++;
  }
  for (int i = k + 1; i < N; ++i) if (cnt[i]) {
    for (int x = k; x < N; x += i) ret[x] += cnt[i];
    if (k == 0) ret[i]--;
  }
  for (int i = 0; i < n; ++i) printf("%d ", ret[h[i]]);
  puts("");
  return 0;
}
