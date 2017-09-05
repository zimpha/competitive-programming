#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 20;
bool G[MAXN][MAXN];
LL dp[1<<MAXN][MAXN];
int n, m;

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++ i) {
        int u, v; cin >> u >> v;
        -- u, -- v;
        G[u][v] = G[v][u] = 1;
        dp[(1 << u) | (1 << v)][max(u, v)] = 1;
    }
    LL ret = 0;
    for (int mask = 0, s = 1 << n; mask < s; ++ mask) {
        int x = __builtin_ctz(mask);
        for (int y = x + 1; y < n; ++ y) if (dp[mask][y]) {
            if (G[x][y]) ret += dp[mask][y];
            for (int z = x + 1; z < n; ++ z) {
                if (G[y][z] && ~mask & 1 << z) dp[mask | 1 << z][z] += dp[mask][y];
            }
        }
    }
    cout << (ret - m) / 2 << endl;
    return 0;
}
