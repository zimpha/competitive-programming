#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 3001;

int sa[N][N], sb[N][N];
int A[N], B[N], dp[N], empty[N];
std::vector<int> pa[N], pb[N];
int n, m, k;

void input(int &n, int a[], int s[][N], std::vector<int> ps[]) {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    ps[a[i]].push_back(i);
  }
  for (int i = 0; i < N; ++i) {
    s[n][i] = 1e9;
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = 0; j < N; ++j) s[i][j] = s[i + 1][j];
    s[i][a[i + 1]] = i + 1;
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 1; j < N; ++j) {
      s[i][j] = std::min(s[i][j], s[i][j - 1]);
    }
  }
}

bool check(int v, int need) {
  if (need == 0 && v == 3) {
    //printf("%d\n", 10);
  }
  for (int i = 0; i <= n; ++i) {
    if (dp[i] == -1) continue;
    int y = sb[dp[i]][v];
    int x = sa[i][v];
    if (!need) {
      if (n - i + m - y >= need && !empty[i]) return true;
      if (n - x + m - dp[i] >= need && dp[i] != 0) return true;
    } else {
      if (n - i + m - y >= need) return true;
      if (n - x + m - dp[i] >= need) return true;
    }
  }
  return false;
}

void update(int v) {
  static int g[N], f[N];
  for (int i = 0; i <= n; ++i) {
    g[i] = -1;
    f[i] = true;
  }
  std::vector<int> &a = pa[v], &b = pb[v];
  for (int i = 0; i <= n; ++i) {
    if (dp[i] == -1) continue;
    int x = -1, y = -1;
    auto it = std::upper_bound(b.begin(), b.end(), dp[i]);
    if (it != b.end()) y = *it;
    it = std::upper_bound(a.begin(), a.end(), i);
    if (it != a.end()) x = *it;
    if (x != -1) {
      if (g[x] == -1 || g[x] >= dp[i]) {
        g[x] = dp[i];
        f[x] = false;
      }
    }
    if (y != -1) {
      if (g[i] == -1 || g[i] > y || (g[i] == y && f[i])) {
        g[i] = y;
        f[i] = empty[i];
      }
    }
  }
  for (int i = 0; i <= n; ++i) {
    dp[i] = g[i];
    empty[i] = f[i];
    if (i && dp[i - 1] != -1) {
      dp[i] = std::min(dp[i], dp[i - 1]);
      if (!empty[i - 1]) empty[i] = false;
    }
  }
}

int main() {
  input(n, A, sa, pa);
  input(m, B, sb, pb);
  scanf("%d", &k);
  for (int i = 0; i <= n; ++i) {
    dp[i] = 0;
    empty[i] = true;
  }
  for (int i = 1; i <= k; ++i) {
    int need = k - i;
    int left = 1, right = N - 1;
    while (left < right) {
      int mid = (left + right - 1) >> 1;
      if (check(mid, need)) right = mid;
      else left = mid + 1;
    }
    update(left);
    printf("%d ", left);
  }
  puts("");
  return 0;
}
