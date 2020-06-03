#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

int main() {
  int n;
  scanf("%d", &n);
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    --a[i];
  }
  std::vector<int> cnt(n);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    for (int x = a[i]; x < n; x += ~x & x + 1) ret ^= cnt[x];
    for (int x = a[i]; x >= 0; x -= ~x & x + 1) cnt[x] ^= 1;
  }
  if (ret != (n & 1)) puts("Um_nik");
  else puts("Petr");
  return 0;
}
