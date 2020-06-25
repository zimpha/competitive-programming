#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 2000 + 10;

int dp[N][N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        dp[i][j] = 2;
      }
    }
    for (int i = 1; i < n; ++i) {
      for (int j = i - 1, k = i + 1; j >= 0 && k < n; ) {
        if (a[i] - a[j] == a[k] - a[i]) {
          dp[i][k] = std::max(dp[i][k], dp[j][i] + 1);
          --j; ++k;
        } else if (a[i] - a[j] < a[k] - a[i]) --j;
        else ++k;
      }
    }
    int ret = 2;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        ret = std::max(ret, dp[i][j]);
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}
