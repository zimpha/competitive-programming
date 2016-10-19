#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
const double lim = 16 * log(10);

map<vector<int>, LL> dp;
int cnt[14];

void gen(int last, int dep, double val) {
  if (dep == 14) {
    vector<int> s;
    for (int i = 0; i < 14; ++i) if (cnt[i]) s.push_back(cnt[i]);
    dp[s] = -1; return;
  }
  for (int i = 0; i <= last; ++i) {
    if (val >= lim) return;
    cnt[dep] = i;
    gen(i, dep + 1, val);
    val += log(p[dep]);
    cnt[dep] = 0;
  }
}

LL solve(vector<int> &s);

LL dfs(vector<int> &s, int d, int o) {
  if (d == 0) {
    if (!o) return 0;
    vector<int> t;
    for (auto x: s) if (x) t.push_back(x);
    sort(t.begin(), t.end(), greater<int>());
    return solve(t);
  }
  LL ret = 0;
  int up = s[d - 1];
  for (int i = 0; i <= up; ++i) {
    s[d - 1] -= i;
    ret += dfs(s, d - 1, o || i);
    if (ret > 1e16) ret = 1e16;
    s[d - 1] += i;
  }
  return ret;
}

LL solve(vector<int> &s) {
  if (!s.size()) return dp[s] = 1;
  if (dp[s] != -1) return dp[s];
  return dp[s] = dfs(s, s.size(), 0);
}

int main() {
  gen(53, 0, 0);
  for (auto &v: dp) {
    vector<int> s = v.first;
    solve(s);
  }
  LL ret = 0;
  for (auto &v: dp) {
    LL n = v.second;
    if (n >= 1e16) continue;
    vector<int> s;
    for (LL i = 2; i * i <= n; ++i) if (n % i == 0) {
      int c = 0;
      while (n % i == 0) ++c, n /= i;
      s.push_back(c);
    }
    if (n > 1) s.push_back(1);
    sort(s.begin(), s.end(), greater<int>());
    if (v.first == s) {
      //cout << v.second << endl;
      ret += v.second;
    }
  }
  cout << ret << endl;
  return 0;
}
