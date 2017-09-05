#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30, SIZE = 1 << 24, inf = 1e9;

int dis[MAXN][MAXN], X[MAXN], Y[MAXN];
int dp[SIZE], pre[SIZE];
int N, S;

inline int sqr(int x) {return x * x;}

int main() {
    scanf("%d%d%d", &X[0], &Y[0], &N); X[N] = X[0], Y[N] = Y[0]; S = 1 << N;
    for (int i = 0; i < N; ++ i) scanf("%d%d", X + i, Y + i);
    for (int i = 0; i <= N; ++ i) {
        for (int j = 0; j <= N; ++ j) {
            dis[i][j] = sqr(X[i] - X[j]) + sqr(Y[i] - Y[j]);
        }
    }
    for (int mask = 0; mask < S; ++ mask) dp[mask] = inf; dp[0] = 0;
    for (int mask = 0; mask < S; ++ mask) {
        if (dp[mask] == inf) continue;
        for (int i = 0; i < N; ++ i) {
            if ((mask >> i) & 1) continue;
            for (int j = i; j < N; ++ j) {
                if ((mask >> j) & 1) continue;
                int mm = mask | (1 << j) | (1 << i);
                int ret = dp[mask] + dis[N][i] + dis[i][j] + dis[j][N];
                if (ret < dp[mm]) dp[mm] = ret, pre[mm] = mask;
            }
            break;
        }
    }
    printf("%d\n0", dp[S - 1]);
    for (int i = S - 1; i; i = pre[i]) {
        for (int t = i ^ pre[i]; t; t -= t & -t) {
            printf(" %d", int(log(t & -t) / log(2) + 1e-8 + 1));
        }
        printf(" 0");
    }
    puts("");
    return 0;
}
