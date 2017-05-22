#include <bits/stdc++.h>

const int N = 300000 + 10;
const int M = 2000 + 10;

double dp[M][M][2];
bool mark[M][M][2];
int p[N], t[N];
int x, n, m;

struct node {
  int x, p, t;
};
std::vector<node> vs;

double solve(int l, int r, int s) {
  if (mark[l][r][s]) return dp[l][r][s];
  mark[l][r][s] = true;
  node now;
  if (s == 0) now = vs[l];
  else now = vs[r];
  double ret = now.t + 1.0 * now.p / 100 * std::abs(now.x - vs[x].x);
  if (l == 0 && r == n - 1) {
    if (vs[l].x == 1 && vs[r].x == m) return ret + (100.0 - now.p) / 100 * std::abs(now.x - vs[x].x);
    else return ret;
    return dp[l][r][s] = ret + (100.0 - now.p) / 100 * std::abs(now.x - vs[x].x);
  }
  double a = 1e20, b = 1e20;
  if (l != 0) a = solve(l - 1, r, 0) + std::abs(now.x - vs[l - 1].x);
  if (r != n - 1) b = solve(l, r + 1, 1) + std::abs(now.x - vs[r + 1].x);
  ret += (100.0 - now.p) / 100 * std::min(a, b);
  return dp[l][r][s] = ret;
}

int main() {
  scanf("%d%d", &n, &x);
  m = n;
  for (int i = 1; i <= n; ++i) scanf("%d%d", p + i, t + i);
  int st = 0;
  int i;
  for (i = x - 1; i >= 1; --i) {
    st += t[i];
    if (p[i] || i == 1) {
      vs.push_back((node){i, p[i], st});
      st = 0;
    }
  }
  while (vs.size() > 1000) vs.pop_back();
  std::reverse(vs.begin(), vs.end());
  int s = vs.size();
  vs.push_back((node){x, p[x], t[x]});
  st = 0;
  for (i = x + 1; i <= n; ++i) {
    st += t[i];
    if (p[i] || i == n) {
      vs.push_back((node){i, p[i], st});
      st = 0;
    }
  }
  while (vs.size() > 2000) vs.pop_back();
  n = vs.size();
  x = s;
  memset(mark, 0, sizeof(mark));
  printf("%.10f\n", solve(x, x, 0));
  return 0;
}
