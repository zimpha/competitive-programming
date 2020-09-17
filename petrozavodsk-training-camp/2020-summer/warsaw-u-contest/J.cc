#include <cstring>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

using int64 = long long;

const int N = 1e4 + 10, M = 10, S = 1100;

int64 a[N][M][M], b[N][M][M];
int64 dp[2][S];
std::vector<int> trans[M][M][S];
int states[S][M];
std::map<std::vector<int>, int> state_id[M][M];
int border[M], ns;
int A, B, C;

void dfs(int d, int bound) {
  if (d == B) {
    for (int i = 0; i < B; ++i) states[ns][i] = border[i];
    state_id[B][C][std::vector<int>(border, border + B)] = ns++;
    return;
  }
  for (int i = bound; i >= 0; --i) {
    border[d] = i;
    dfs(d + 1, i);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  assert(1 <= T && T <= 10000);
  int sum = 0;
  for (int cas = 1; cas <= T; ++cas) {
    scanf("%d%d%d", &A, &B, &C);
    assert(1 <= A && A <= 10000);
    assert(1 <= B && B <= 6);
    assert(1 <= C && C <= 6);
    sum += A;
    assert(1 <= sum && sum <= 10000);
    for (int i = 0; i < A; ++i) {
      for (int j = 0; j < B; ++j) {
        for (int k = 0; k < C; ++k) scanf("%lld", &a[i][j][k]);
        a[i][j][C] = 0;
        for (int k = C - 1; k >= 0; --k) a[i][j][k] += a[i][j][k + 1];
      }
    }
    for (int i = 0; i < A; ++i) {
      for (int j = 0; j < B; ++j) {
        for (int k = 0; k < C; ++k) scanf("%lld", &b[i][j][k]);
        b[i][j][C] = b[i][j][C + 1] = 0;
        for (int k = C - 1; k >= 0; --k) b[i][j][k] += b[i][j][k + 1];
      }
    }
    if (state_id[B][C].empty()) {
      ns = 0;
      dfs(0, C);
      assert(ns < S);
      for (int i = 0; i < ns; ++i) {
        trans[B][C][i].clear();
        for (int j = 0; j < B; ++j) border[j] = states[i][j];
        for (int j = 0; j < B; ++j) if (states[i][j] < C) {
          if (j && border[j] + 1 > border[j - 1]) continue;
          border[j]++;
          trans[B][C][i].push_back(state_id[B][C][std::vector<int>(border, border + B)]);
          border[j]--;
        }
      }
    } else {
      ns = state_id[B][C].size();
      for (auto &x: state_id[B][C]) {
        for (int j = 0; j < B; ++j) states[x.second][j] = x.first[j];
      }
    }
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < A; ++i) {
      int u = i & 1, v = u ^ 1;
      for (int x = 0; x < ns; ++x) dp[v][x] = dp[u][x];
      for (int x = 0; x < ns; ++x) {
        for (auto y: trans[B][C][x]) dp[v][x] = std::max(dp[v][x], dp[v][y]);
      }
      for (int x = 0; x < ns; ++x) {
        int64 sa = 0, sb = 0;
        for (int j = 0; j < B; ++j) {
          sa += a[i][j][states[x][j]];
          sb += b[i][j][states[x][j]];
        }
        dp[v][x] += sa - sb;
      }
    }
    int64 ret = 0;
    for (int i = 0; i < ns; ++i) {
      ret = std::max(ret, dp[A & 1][i]);
    }
    if (ret > 0) puts("NIE");
    else puts("TAK");
  }
  return 0;
}
