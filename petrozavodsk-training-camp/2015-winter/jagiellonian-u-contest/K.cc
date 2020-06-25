#include <cstdio>
#include <cstring>
#include <algorithm>

int dp[19683], mark[19683];
int a[3][3];

void decode(int u) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      a[i][j] = u % 3;
      u /= 3;
    }
  }
}

int encode() {
  int p = 1, r = 0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      r += p * a[i][j];
      p *= 3;
    }
  }
  return r;
}

bool end() {
  for (int i = 0; i < 3; ++i) if (a[i][0]) {
    if (a[i][0] == a[i][1] && a[i][0] == a[i][2]) return true;
  }
  for (int i = 0; i < 3; ++i) if (a[0][i]) {
    if (a[0][i] == a[1][i] && a[0][i] == a[2][i]) return true;
  }
  if (a[0][0] && a[0][0] == a[1][1] && a[0][0] == a[2][2]) return true;
  if (a[0][2] && a[0][2] == a[1][1] && a[0][2] == a[2][0]) return true;
  return false;
}

int dfs1(int u, int w) {
  if (dp[u] != -1) return dp[u];
  decode(u);
  dp[u] = 0;
  if (end()) return dp[u];
  int cnt = 0;
  for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) cnt += !!a[i][j];
  if (cnt == 9) return dp[u] = 1;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (a[i][j]) continue;
      a[i][j] = w;
      dp[u] = std::max(dp[u], 2 - dfs1(encode(), 3 - w));
      a[i][j] = 0;
    }
  }
  return dp[u];
}

void dfs2(int u, int w) {
  mark[u] = true;
  decode(u);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (a[i][j]) continue;
      a[i][j] = w;
      int v = encode();
      if (!mark[v] && dp[v] == 1) dfs2(v, 3 - w);
      a[i][j] = 0;
    }
  }
}

int main() {
  memset(dp, -1, sizeof(dp));
  dfs1(0, 1);
  dfs2(0, 1);
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    for (int i = 0; i < 3; ++i) {
      static char s[10];
      scanf("%s", s);
      for (int j = 0; j < 3; ++j) {
        a[i][j] = s[j] == '.' ? 0 : (s[j] == 'O' ? 1 : 2);
      }
    }
    int u = encode();
    if (dp[u] == -1) puts("INVALID");
    else if (!mark[u]) puts("UNREACHABLE");
    else puts("REACHABLE");
  }
  return 0;
}
