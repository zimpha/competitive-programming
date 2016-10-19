#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int MAXN = 50000000;
int mp[MAXN];

void sieve() {
  for (int i = 2; i < MAXN; ++i) if (!mp[i]) {
    for (int j = i; j < MAXN; j += i) {
      if (!mp[j]) mp[j] = i;
    }
  }
}

int ok(int y, int n) {
  assert(n % y == 0);
  int d = n / y + y;
  if (d % 4) return 0;
  d /= 4;
  int x = y + d, z = y - d;
  return z > 0;
}

int dfs(int dep, vector<PII> &pf, int n, int val = 1) {
  if (dep == pf.size()) return ok(val, n);
  int ret = 0;
  for (size_t i = 0; i <= pf[dep].second; ++i) {
    ret += dfs(dep + 1, pf, n, val);
    if (ret > 1) return ret;
    val *= pf[dep].first;
  }
  return ret;
}

int sol(int n) {
  int ret = 0;
  vector<PII> pf;
  for (int x = n; x > 1; x /= mp[x]) {
    if (pf.empty() || pf.back().first != mp[x]) {
      pf.push_back(PII(mp[x], 1));
    }
    else pf.rbegin()->second++;
  }
  return dfs(0, pf, n);
}

int run(int upp, int cnt) {
  int ret = 0;
  for (int i = 1; i < upp; ++i) {
    ret += sol(i) == cnt;
  }
  return ret;
}

int main() {
  sieve();
  cout << run(100, 1) << endl;
  cout << run(50000000, 1) << endl;
  return 0;
}
