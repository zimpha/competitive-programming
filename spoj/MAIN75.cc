#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 500 + 10, MOD = 1e9 + 7;
int dp[MAXN][MAXN];

int solve(int n, int h) {
    if (h < 0) return 0;
    if (dp[n][h] != -1) return dp[n][h];
    if (n == 0) return dp[n][h] = 1;
    dp[n][h] = 0;
    for (int i = 1; i <= n; ++ i) {
        dp[n][h] += (LL)solve(i - 1, h - 1) * solve(n - i, h - 1) % MOD;
        dp[n][h] %= MOD;
    }
    return dp[n][h];
}

int main() {
    int T; scanf("%d", &T);
    memset(dp, -1, sizeof(dp));
    while (T --) {
        int n, h; scanf("%d%d", &n, &h); ++ h;
        printf("%d\n", (solve(n, h) - solve(n, h - 1) + MOD) % MOD);
    }
    return 0;
}

