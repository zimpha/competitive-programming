#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  int p, k, n;
  scanf("%d%d%d", &p, &k, &n);
  std::vector<int> a, b;
  std::vector<int> xs = {p * 2, k * 2};
  for (int i = 0; i < n; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    l = std::max(l, p);
    r = std::min(r, k);
    if (l > r) continue;
    a.push_back(l);
    b.push_back(r);
    xs.push_back(l * 2);
    xs.push_back(r * 2);
    if (p <= l - 1) xs.push_back(l * 2 - 1);
    if (r + 1 <= k) xs.push_back(r * 2 + 1);
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  std::vector<int> cnt(xs.size() + 1);
  n = a.size();
  for (int i = 0; i < n; ++i) {
    a[i] = std::lower_bound(xs.begin(), xs.end(), a[i] * 2) - xs.begin();
    b[i] = std::lower_bound(xs.begin(), xs.end(), b[i] * 2) - xs.begin();
    cnt[a[i]]++, cnt[b[i] + 1]--;
  }
  int mi = -1, mx = -1;
  for (size_t i = 0; i < xs.size(); ++i) {
    cnt[i + 1] += cnt[i];
    if (mi == -1 || mi > cnt[i]) mi = cnt[i];
    if (mx == -1 || mx < cnt[i]) mx = cnt[i];
  }
  printf("%d %d\n", mi, mx);
  return 0;
}
