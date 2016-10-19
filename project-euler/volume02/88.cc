#include <bits/stdc++.h>
using namespace std;

vector<int> ret;

void dfs(int n, int d, int c, int p, int s) {
  if (d > n) return;
  if (p == s) ret[d] = min(s, ret[d]);
  for (int i = c; ; ++ i) {
    if (p == 1 && i > 100) break;
    if (1ll * p * i > s + i) break;
    dfs(n, d + 1, i, p * i, s + i);
  }
}

int sol(int n) {
  ret.assign(n + 1, 1e9);
  for (int one = 0; one <= n; ++ one) {
    dfs(n, one, 2, 1, one);
  }
  sort(ret.begin(), ret.end());
  ret.erase(unique(ret.begin(), ret.end()), ret.end());
  ret.pop_back();
  return accumulate(ret.begin() + 1, ret.end(), 0);
}

int main() {
  cout << sol(6) << endl;
  cout << sol(12) << endl;
  cout << sol(12000) << endl;
  return 0;
}
