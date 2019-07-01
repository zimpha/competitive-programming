#include <cstdio>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        int n, m;
        scanf("%d%d", &n, &m);
        std::vector<std::vector<int>> g(n, std::vector<int>(n, -1));
        std::vector<int> x(m), y(m), z(m);
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &x[i], &y[i], &z[i]);
            --x[i], --y[i];
            g[x[i]][y[i]] = g[y[i]][x[i]] = z[i];
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (g[i][k] == -1 || g[k][j] == -1) continue;
                    if (g[i][j] == -1 || g[i][j] > g[i][k] + g[k][j]) {
                        g[i][j] = g[i][k] + g[k][j];
                    }
                }
            }
        }
        bool valid = true;
        for (int i = 0; i < m; ++i) {
            if (g[x[i]][y[i]] != z[i]) valid = false;
        }
        if (!valid) printf("Case #%d: Impossible\n", cas);
        else {
            printf("Case #%d: %d\n", cas, m);
            for (int i = 0; i < m; ++i) {
                printf("%d %d %d\n", x[i] + 1, y[i] + 1, z[i]);
            }
        }
    }
    return 0;
}
