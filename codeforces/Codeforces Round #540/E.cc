#include <cstdio>

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (n > 1ll * k * k - k) {
    puts("NO");
    return 0;
  }
  puts("YES");
  for (int s = 2; s <= k + k && n; ++s) {
    int l = 1, r = k;
    if (s >= k + 2) l = s - k;
    for (int i = l; i <= r && i < s && n; ++i) {
      if (i == s - i) continue;
      printf("%d %d\n", i, s - i);
      --n;
    }
  }
  return 0;
}
