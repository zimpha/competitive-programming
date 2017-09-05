#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

int H[MAXN], ret[MAXN];
int n, a, b, ans;

bool dfs(int dep, int x, int cur) {
    if (dep == 0) {
        for (int i = 1; i <= n; ++ i) {
            if (H[i] >= 0) return false;
        }
        return true;
    }
    if (H[x] < 0) return dfs(dep, x + 1, cur);
    if (x == n) {
        H[n] -= b; ret[dep] = n - 1;
        if (dfs(dep - 1, x, cur)) return true;
        H[n] += b;
    }
    else {
        for (int i = max(x, cur); i <= x + 1; ++ i) {
            if (i <= 1 || i >= n) continue;
            ret[dep] = i;
            H[i] -= a; H[i - 1] -= b; H[i + 1] -= b;
            if (dfs(dep - 1, x, i)) return true;
            H[i] += a; H[i - 1] += b; H[i + 1] += b;
        }
    }
    return false;
}

int main() {
    cin >> n >> a >> b;
    for (int i = 1; i <= n; ++ i) cin >> H[i];
    for (ans = 1; ; ++ ans) {
        if (dfs(ans, 1, 2)) {
            printf("%d\n", ans);
            for (int i = 1; i <= ans; ++ i) printf("%d%c", ret[i], " \n"[i == ans]);
            break;
        }
    }
    return 0;
}
