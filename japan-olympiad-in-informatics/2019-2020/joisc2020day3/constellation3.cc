#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using int64 = long long;

const int N = 200000 + 10;

struct Value {
  std::map<int, int64> mp;
  int64 delta;
  void trunc(int h) {
    int64 ret = 0;
    for (auto it = mp.begin(); it != mp.end(); it = mp.erase(it)) {
      if (it->first > h) break;
      ret = std::max(ret, it->second);
    }
    mp.emplace(h, ret);
  }
  void merge(Value &rhs, int h) {
    if (mp.size() < rhs.mp.size() && mp.count(h)) {
      std::swap(mp, rhs.mp);
      std::swap(delta, rhs.delta);
    }
    int64 extra = mp[h] + delta;
    delta += rhs.mp[h] + rhs.delta;
    for (auto &e: rhs.mp) if (e.first > h) {
      mp[e.first] = std::max(mp[e.first] + delta, e.second + rhs.delta + extra) - delta;
    }
    rhs.mp.clear();
  }
} dp[N];

std::vector<std::pair<int, int>> stars[N];

int main() {
  int n, m;
  scanf("%d", &n);
  std::vector<int> a(n), idx(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    idx[i] = i;
    dp[i].delta = 0;
    dp[i].mp.emplace(a[i], 0);
  }
  scanf("%d", &m);
  int64 sum = 0;
  for (int i = 0; i < m; ++i) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    dp[x - 1].mp.emplace(y, c);
    sum += c;
  }
  std::sort(idx.begin(), idx.end(), [&](int x, int y) {
    return a[x] < a[y];
  });
  std::vector<int> prev(n, -1), next(n, -1);
  for (auto &i: idx) {
    int l = i, r = i;
    if (i > 0 && prev[i - 1] != -1) {
      l = prev[i - 1];
      dp[l].trunc(a[i]);
      dp[i].merge(dp[l], a[i]);
    }
    if (i < n - 1 && next[i + 1] != -1) {
      r = next[i + 1];
      dp[i + 1].trunc(a[i]);
      dp[i].merge(dp[i + 1], a[i]);
    }
    std::swap(dp[l], dp[i]);
    prev[r] = l; next[l] = r;
  }
  dp[0].trunc(n);
  printf("%lld\n", sum - dp[0].delta - dp[0].mp[n]);
  return 0;
}
