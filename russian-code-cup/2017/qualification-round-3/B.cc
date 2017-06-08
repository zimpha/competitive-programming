#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, H, A;
    scanf("%d%d%d", &n, &H, &A);
    std::vector<int> hit(n);
    for (int i = 0; i < n; ++i) {
      int h, a;
      scanf("%d%d", &h, &a);
      hit[i] = std::min<long long>(H + 1, 1ll * (h + A - 1) / A * a);
    }
    std::sort(hit.begin(), hit.end());
    int sum = 0;
    while (sum < H && hit.size()) {
      sum += hit.back();
      if (sum >= H) break;
      hit.pop_back();
    }
    if (sum < H) puts("-1");
    else printf("%d\n", n - (int)hit.size());
  }
  return 0;
}
