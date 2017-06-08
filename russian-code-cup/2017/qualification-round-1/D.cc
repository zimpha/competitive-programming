#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

const int N = 1000000 + 10;

using ll = long long;

std::vector<int> block[N];
std::vector<int> erase[N];
ll dp[N], upd[N];
int s[N];
int n, k, q;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 0; i < q; ++i) {
      block[i].clear();
      erase[i].clear();
      scanf("%d", s + i);
      dp[i] = -1;
    }
    for (int i = 0; i < q; ++i) {
      int c;
      scanf("%d", &c);
      block[i].resize(c);
      for (int j = 0; j < c; ++j) {
        scanf("%d", &block[i][j]);
      }
    }
    std::multiset<ll> val;
    std::vector<int> cnt(n + 1, 0);
    int last = 0, all = 0;
    for (int i = 0, j = 0; i < q; ++i) {
      for (auto &&e: erase[i]) {
        val.erase(val.find(upd[e]));
      }
      while (j < q && all <= k) {
        for (auto &&e: block[j]) {
          cnt[e]++;
          if (cnt[e] == 1) ++all;
        }
        ++j;
      }
      if (all <= k) last = j;
      else last = j - 1;
      erase[last].push_back(i);
      ll p = i ? dp[i - 1] : -s[i];
      upd[i] = p + s[i];
      val.insert(upd[i]);
      dp[i] = *val.begin();
      for (auto &&e: block[i]) {
        cnt[e]--;
        if (cnt[e] == 0) --all;
      }
    }
    printf("%lld\n", dp[q - 1]);
  }
  return 0;
}
