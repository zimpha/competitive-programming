#include <cstdio>
#include <algorithm>
#include <vector>

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> l(n), r(n), xs(n * 4);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d", &l[i], &r[i]);
      l[i] *= 2; r[i] *= 2;
      xs[i * 4] = l[i] - 1;
      xs[i * 4 + 1] = l[i];
      xs[i * 4 + 2] = r[i];
      xs[i * 4 + 3] = r[i] + 1;
    }
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    int m = xs.size();
    std::vector<int> cnt(m + 1);
    for (int i = 0; i < n; ++i) {
      l[i] = std::lower_bound(xs.begin(), xs.end(), l[i]) - xs.begin();
      r[i] = std::lower_bound(xs.begin(), xs.end(), r[i]) - xs.begin();
      cnt[l[i]]++; cnt[r[i] + 1]--;
    }
    int total = 0, one = 0;
    std::vector<int> id(m + 1, -1);
    for (int i = 1; i <= m; ++i) {
      cnt[i] += cnt[i - 1];
      if (cnt[i] && !cnt[i - 1]) ++total;
      if (cnt[i] == 1 && cnt[i - 1] != 1) id[i] = one++;
      else id[i] = id[i - 1];
    }
    //for (int i = 0; i <= m; ++i) printf("%d ", cnt[i]);
    //puts("");
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      //printf("l=%d r=%d\n", l[i], r[i]);
      int now = total + id[r[i]] - id[l[i]];
      if (cnt[r[i]] == 1) --now;
      if (now > ret) ret = now;
    }
    printf("%d\n", ret);
  }
  return 0;
}
