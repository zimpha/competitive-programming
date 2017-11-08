#include <bits/stdc++.h>
using namespace std;

class Solution {
  static const int MAXN = 10000 + 10;
  int dp[MAXN], src[MAXN];
  int vs[MAXN], pl[MAXN], n, m;
  vector<int> sp;
  void sieve() {
    m = 0; sp.clear();
    for (int i = 2; i <= n; ++i) vs[i] = 1;
    for (int i = 2; i <= n; ++i) if (vs[i]) {
      pl[++m] = i;
      for (int j = i * 2; j <= n; j += i) vs[j] = 0;
    }
    for (int i = 1; i <= m; ++i) if (vs[i]) {
      sp.push_back(pl[i]);
    }
  }
public:
  void run() {
    scanf("%d", &n);
    sieve();
    for (int i = 0; i <= n; ++i) dp[i] = -1;
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
      for (auto &x: sp) if (i >= x && dp[i - x] != -1) {
        if (dp[i] == -1 || dp[i] > dp[i - x] + 1) {
          dp[i] = dp[i - x] + 1;
          src[i] = x;
        }
      }
    }
    vector<int> ret;
    if (dp[n] == -1) puts("0");
    else {
      for (int i = n; i; i -= src[i]) ret.push_back(src[i]);
      sort(ret.begin(), ret.end(), greater<int>());
      printf("%d\n", dp[n]);
      for (auto &x: ret) printf("%d ", x); puts("");
    }
  }
} sol;

int main() {
  sol.run();
  return 0;
}
