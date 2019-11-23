#include <cstdio>
#include <vector>
#include <algorithm>

bool solve(int n, int m, std::vector<int> a) {
  std::vector<int> order(m + 1, -1), seq;
  std::vector<int> len(n, 0), cnt(m + 1, 0);
  int idx = 0;
  for (auto &v: a) {
    if (order[v] == -1) order[v] = ++idx, seq.push_back(v);
    if (cnt[v] == n) continue;
    if (len[cnt[v]] == order[v] - 1) ++len[cnt[v]], ++cnt[v];
  }
  int mx = len.back();
  cnt.assign(m + 1, 0);
  for (int i = 0; i < mx; ++i) cnt[seq[i]]++;
  std::vector<int> u;
  for (int i = 1; i <= m; ++i) if (cnt[i] == 0) {
    u.push_back(i);
  }
  for (int i = mx; i < idx; ++i) {
    if (u[i - mx] != seq[i]) return false;
  }
  return true;
}

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  std::vector<int> a(q);
  for (int i = 0; i < q; ++i) {
    scanf("%d", &a[i]);
  }
  std::reverse(a.begin(), a.end());
  if (solve(n, m, a)) puts("Yes");
  else puts("No");
  return 0;
}
