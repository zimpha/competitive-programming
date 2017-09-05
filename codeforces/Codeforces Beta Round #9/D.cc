
 #include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL dp[40][40];

LL calc(int n, int h) {
    if (dp[n][h] != -1) return dp[n][h];
    if (n == 0 && h == 0) return dp[n][h] = 1;
    if (h == 0 || n == 0) return dp[n][h] = 0;
    dp[n][h] = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = 0; j <= h - 1; ++ j) {
            dp[n][h] += calc(i - 1, h - 1) * calc(n - i, j);
            dp[n][h] += calc(n - i, h - 1) * calc(i - 1, j);
        }
        dp[n][h] -= calc(i - 1, h - 1) * calc(n - i, h - 1);
    }
    return dp[n][h];
}

int main() {
    memset(dp, -1, sizeof(dp));
    int n, h;
    cin >> n >> h;
    LL ret = 0;
    for (int i = h; i <= n; ++ i) ret += calc(n, i);
    cout << ret << endl;
    return 0;
}
