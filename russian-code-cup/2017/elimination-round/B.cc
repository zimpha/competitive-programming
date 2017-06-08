#include <bits/stdc++.h>

using ll = long long;

const int N = 2000 + 10;

ll dp[N][N][2];
bool key[N][26];
int n, a, b, c;
char s[N];

struct node {
  int i, j, e;
};

void upd(ll &x, ll y) {
  if (x == -1 || y < x) x = y;
}

int main() {
  scanf("%d%d%d%d", &n, &a, &b, &c);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    memset(key[i], 0, sizeof(key[i]));
    for (int j = 0; s[j]; ++j) key[i][s[j] - 'a'] = 1;
  }
  scanf("%s", s + 1);
  int m = strlen(s + 1);
  memset(dp, -1, sizeof(dp));
  dp[0][0][0] = 0;
  for (int i = 1; i <= n; ++i) {
    dp[0][i % n][1] = dp[0][0][0] + a + 1ll * b * (i - 1);
  }
  for (int i = 0; i < m; ++i) {
    using pii = std::pair<ll, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> q;
    for (int j = 0; j < n; ++j) {
      if (dp[i][j][0] != -1) {
        q.emplace(dp[i][j][0] + a - ll(j + 1) * b, j);
      }
    }
    for (int j = n; j < 2 * n; ++j) {
      while (q.size() && q.top().second < j - n) q.pop();
      if (q.size()) dp[i][j % n][1] = q.top().first + 1ll * j * b;
      if (dp[i][j % n][0] != -1) {
        q.emplace(dp[i][j % n][0] + a - ll(j + 1) * b, j);
      }
    }
    int v = s[i + 1] - 'a';
    for (int j = 0; j < n; ++j) {
      if (key[j][v]) {
        if (dp[i][j][0] != -1) {
          upd(dp[i + 1][j][0], dp[i][j][0] + c);
        }
        if (dp[i][j][1] != -1) {
          upd(dp[i + 1][j][0], dp[i][j][1] + c);
        }
      }
    }
  }
  ll ret = -1;
  for (int i = 0; i < n; ++i) {
    if (dp[m][i][0] != -1) upd(ret, dp[m][i][0]);
    if (dp[m][i][1] != -1) upd(ret, dp[m][i][1]);
  }
  printf("%lld\n", ret);
  return 0;
}
