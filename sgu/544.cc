#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
const int MAXN = 500 + 10, M = 1e9 + 9;

PII player[MAXN << 1];
int dp[2][MAXN][MAXN];
int s[MAXN << 1];
int n, k;

void upd(int &x, int y) {
  x += y; if (x >= M) x -= M;
}

void run() {
  cin >> n >> k;
  if (n % 2 != k % 2) {puts("0"); return;}
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    player[i] = PII(x, 1);
  }
  for (int i = 0; i < n; ++i) {
    int x; cin >> x;
    player[i + n] = PII(x, 0);
  }
  int m = (n + k) / 2;
  sort(player, player + n * 2);
  for (int i = 0; i < n * 2; ++i) {
    if (!i) s[i] = player[i].second;
    else s[i] = s[i - 1] + player[i].second;
  }
  int x = 0, y = 1; dp[x][0][0] = 1;
  for (int i = 0; i < n * 2; ++i) {
    for (int a = 0; a <= m; ++a) {
      for (int b = 0; b <= n; ++b) {
        dp[y][a][b] = 0;
      }
    }
    int type = player[i].second;
    int ss = i ? s[i - 1] : 0, tt = i - ss;
    for (int a = 0; a <= m && a <= ss; ++a) {
      for (int b = 0; b <= ss - a; ++b) if (dp[x][a][b]) {
        if (type) {
          int un = tt - ss + b;
          if (un > 0) upd(dp[y][a + 1][b], 1ll * dp[x][a][b] * un % M);
          upd(dp[y][a][b + 1], dp[x][a][b]);
        } else {
          if (b) upd(dp[y][a][b - 1], 1ll * dp[x][a][b] * b % M);
          upd(dp[y][a][b], dp[x][a][b]);
        }
      }
    }
    swap(x, y);
  }
  printf("%d\n", dp[x][m][0]);
}

int main() {
  run();
  return 0;
}
