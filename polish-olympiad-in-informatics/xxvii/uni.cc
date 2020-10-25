#include <cstdio>
#include <cassert>
#include <algorithm>

using i64 = long long;

// x in [0, r], y in [l, 2^d-1]
i64 bridge(i64 l, i64 r, int d) {
  if (r >= l) return 0;
  i64 mask = i64(1) << (d - 1);
  if (l & mask) {
    if (r & mask) return bridge(l ^ mask, r ^ mask, d - 1);
    else return mask + bridge(l ^ mask, r, d - 1);
  } else {
    assert((r & mask) == 0);
    return bridge(l, r, d - 1);
  }
}

i64 solve(i64 l, i64 r, int d) {
  if (l == r) return 0;
  while (~r >> d & 1) --d;
  i64 mask = i64(1) << d;
  if (l == 0 && r == mask * 2 - 1) {
    return solve(0, r ^ mask, d - 1) * 2 + mask;
  }
  if (l & mask) {
    return solve(l ^ mask, r ^ mask, d - 1);
  } else {
    return solve(l, mask - 1, d - 1) + solve(0, r ^ mask, d - 1) + bridge(l, r ^ mask, d) + mask;
  }
}

int main() {
  int q;
  scanf("%d", &q);
  for (int it = 0; it < q; ++it) {
    i64 a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld\n", solve(a, b, 60));
  }
  return 0;
}
