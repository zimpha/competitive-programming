#include <cstdio>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>

using int64 = long long;

std::vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73};
int cnt[100];
int64 n;

int ret;
int64 ret_x, ret_y;
std::vector<int> ways;
std::vector<std::vector<int>> factors;
std::vector<int64> candidates;
int div_bound;

void dfs_hcn(int d, int e, int64 now, int ds) {
  ways.push_back(ds);
  for (int i = 1; i <= e; ++i) {
    now *= primes[d];
    if (now > n) break;
    dfs_hcn(d + 1, i, now, ds * (i + 1));
  }
}

void dfs1(int d, int e, int64 now, int ds, int bound) {
  if (d == 14 || now * primes[d] > n) {
    if (ds >= div_bound) {
      candidates.push_back(now);
      factors.emplace_back(cnt, cnt + d);
      ways.push_back(ds);
    }
    return;
  }
  for (int j = d; j < 14; ++j) {
    int64 t_now = now;
    int upp = bound ? e + 1 : e;
    for (int i = 1; i <= upp; ++i) {
      t_now *= primes[j];
      if (t_now > n) break;
      cnt[j] = i;
      dfs1(j + 1, i, t_now, ds * (i + 1), bound -= (i > e));
      cnt[j] = 0;
    }
  }
}

void dfs2(int d, int e, int64 now, int ds, int bound) {
  if (d == 14 || now * primes[d] > n) {
    if (ds < div_bound) return;
    for (size_t i = 0; i < candidates.size(); ++i) {
      int dd = factors[i].size(), total = 1, prefix = 1, sum = ways[i];
      for (int j = 0; j < d; ++j) total *= (cnt[j] + 1);
      for (int j = 0; j < d; ++j) {
        int u = j < dd ? factors[i][j] : 0;
        total /= cnt[j] + 1;
        if (cnt[j] > u) sum += prefix * total * (cnt[j] - u);
        prefix *= std::min(cnt[j], u) + 1;
      }
      if (sum > ret) ret = sum, ret_x = now, ret_y = candidates[i];
    }
    return;
  }
  for (int j = d; j < 14; ++j) {
    int64 t_now = now;
    int upp = bound ? e + 1 : e;
    for (int i = 1; i <= upp; ++i) {
      t_now *= primes[j];
      if (t_now > n) break;
      cnt[j] = i;
      dfs2(j + 1, i, t_now, ds * (i + 1), bound -= (i > e));
      cnt[j] = 0;
    }
  }
}

int main() {
  scanf("%lld", &n);
  dfs_hcn(0, 53, 1, 1);
  std::sort(ways.begin(), ways.end());
  ways.erase(std::unique(ways.begin(), ways.end()), ways.end());
  std::reverse(ways.begin(), ways.end());
  while (ways.size() > 10) ways.pop_back();
  div_bound = ways.back();
  ways.clear();
  dfs1(0, 10, 1, 1, 2);
  ret = -1;
  dfs2(0, 10, 1, 1, 2);
  printf("%d\n", ret);
  printf("%lld %lld\n", ret_x, ret_y);
  return 0;
}
