// http://www.spoj.com/problems/RSORTING/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int MAXN = 1000 + 10, inf = 1e9;

int dp[MAXN][MAXN], pre[MAXN][MAXN];
int A[MAXN], P[MAXN], vis[MAXN], n;

void print() {
  vector<PII> moves;
  vector<int> e;
  for (int i = 0; i <= n; ++ i) e.push_back(A[i]);
  for (int i = n; i >= 0; -- i) if (!vis[i]) {
    int s = find(e.begin(), e.end(), i) - e.begin();
    e.erase(e.begin() + s);
    int t = find(e.begin(), e.end(), i + 1) - e.begin();
    e.insert(e.begin() + t, i);
    moves.push_back(PII(s + 1, t + 1));
  }
  printf("%d\n", (int)moves.size());
  for (auto &x : moves) printf("%d %d\n", x.first, x.second);
}

void solve() {
  for (int i = 0; i < n; ++ i) dp[n][i] = inf; dp[n][n] = 0;
  for (int i = n - 1; i >= 0; -- i) {
    int v1 = 1, v2 = 1, add = 0;
    for (int j = 0; j < P[i]; ++ j) v1 += (A[j] < i);
    for (int j = 0; j <= n; ++ j) {
      v2 += (A[j] < i);
      dp[i][j] = dp[i + 1][j] + v1 + v2;
      pre[i][j] = j;
    }
    for (int j = P[i] + 1; j <= n; ++ j) {
      int tmp = dp[i + 1][j] + add;
      if (dp[i][P[i]] > tmp) {
        dp[i][P[i]] = tmp;
        pre[i][P[i]] = j;
      }
      if (A[j] < i) add += i - A[j];
    }
  }
  int mx = inf, id = -1;
  for (int i = 0; i <= n; ++ i) {
    if (mx > dp[0][i]) mx = dp[0][i], id = i;
  }
  memset(vis, 0, sizeof(vis)); vis[n] = true;
  for (int i = 0; i < n; ++ i) {
    vis[i] = (id == P[i]);
    id = pre[i][id];
  }
  print();
}

int main() {

  while (scanf("%d", &n) == 1) {
    map<int, int> mp;
    for (int i = 0; i < n; ++ i) {
      int v; scanf("%d", &v);
      mp[-v] = i;
    }
    n = 0;
    for (auto &x : mp) A[x.second] = n ++; A[n] = n;
    for (int i = 0; i <= n; ++ i) P[A[i]] = i;
    solve();
  }
  return 0;
}
