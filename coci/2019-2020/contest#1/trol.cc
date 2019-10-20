#include <cstdio>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int64 l, r;
    scanf("%lld%lld", &l, &r);
    --l;
    int64 kr = r / 9, mr = r % 9;
    int64 kl = l / 9, ml = l % 9;
    printf("%lld\n", kr * 45 + (1 + mr) * mr / 2 - kl * 45 - (ml + 1) * ml / 2);
  }
  return 0;
}
