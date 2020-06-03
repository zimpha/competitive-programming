#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int N = 5e5 + 10, M = 5e5 + 10;

std::vector<int> med[M];
int l[N], r[N], c[M];
int64 ret[N], total;

void solve(const std::vector<int> &doctors, int mid) {
  std::vector<int> xs;
  for (auto &x: doctors) {
    xs.push_back(l[x]);
    xs.push_back(r[x] + 1);
  }
  std::sort(xs.begin(), xs.end());
  xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
  std::vector<int> cnt(xs.size());
  for (auto &x: doctors) {
    int pl = std::lower_bound(xs.begin(), xs.end(), l[x]) - xs.begin();
    int pr = std::lower_bound(xs.begin(), xs.end(), r[x] + 1) - xs.begin();
    cnt[pl]++; cnt[pr]--;
  }
  for (size_t i = 1; i < cnt.size(); ++i) {
    cnt[i] += cnt[i - 1];
  }
  std::vector<int> sum(cnt.size());
  for (int i = cnt.size() - 1; i >= 0; --i) {
    if (i + 1 == cnt.size()) sum[i] = 0;
    else sum[i] = sum[i + 1];
    if (cnt[i] == 1) sum[i] += xs[i + 1] - xs[i];
    if (cnt[i]) total += int64(xs[i + 1] - xs[i]) * c[mid];
  }
  for (auto &x: doctors) {
    int pl = std::lower_bound(xs.begin(), xs.end(), l[x]) - xs.begin();
    int pr = std::lower_bound(xs.begin(), xs.end(), r[x] + 1) - xs.begin();
    ret[x] -= int64(sum[pl] - sum[pr]) * c[mid];
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) scanf("%d", &c[i]);
  for (int i = 0, k; i < n; ++i) {
    scanf("%d%d%d", &l[i], &r[i], &k);
    for (int j = 0, x; j < k; ++j) {
      scanf("%d", &x);
      med[x - 1].push_back(i);
    }
  }
  for (int i = 0; i < m; ++i) {
    solve(med[i], i);
  }
  for (int i = 0; i < n; ++i) {
    printf("%lld ", ret[i] + total);
  }
  puts("");
  return 0;
}
