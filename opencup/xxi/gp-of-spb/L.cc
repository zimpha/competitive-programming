#include <cstdio>
#include <vector>

using u64 = unsigned long long;

u64 mark[31251];
u64 shifts[64][64];

void set(u64 *a, int x) {
  a[x / 64] |= u64(1) << (x % 64);
}

int main() {
  int n, l, r;
  scanf("%d%d%d", &n, &l, &r);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    for (int s = 0; s < 64; ++s) {
      set(shifts[s], a[i] - a[0] + s);
    }
  }
  std::vector<int> now;
  for (int i = 0; i < r; ++i) {
    if (r - i >= l) now.push_back(a[0] * (r - i));
    std::vector<int> tmp;
    for (auto &x: now) {
      int s = x % 64, r = x / 64;
      for (int k = 0; k < 64; ++k) {
        u64 upd_mask = (~mark[r + k]) & shifts[s][k];
        mark[r + k] |= upd_mask;
        while (upd_mask) {
          int y = __builtin_ctzll(upd_mask);
          tmp.push_back((r + k) * 64 + y);
          upd_mask ^= u64(1) << y;
        }
      }
    }
    now = tmp;
  }
  int ret = 0;
  for (int i = 0; i < 31251; ++i) {
    ret += __builtin_popcountll(mark[i]);
  }
  printf("%d\n", ret);
  return 0;
}
