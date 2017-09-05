#include <bits/stdc++.h>
using namespace std;

const int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
const int MAXN = 300 + 10;
char a[MAXN][MAXN];
int n, m;

void dfs(int x, int y, int& s) {
    if (x < 0 || x >= n || y < 0 || y >= m || a[x][y] != '1') return;
    a[x][y] = '2'; ++ s;
    for (int i = 0; i < 8; ++ i) dfs(x + dx[i], y + dy[i], s);
}

bool check(int x, int y, int d, int l, int r) {
    for (int i = 0; i <= d; ++ i) {
        for (int j = l; j < r; ++ j) {
            if (x + dx[j] * i < 0 || x + dx[j] * i >= n) return 0;
            if (y + dy[j] * i < 0 || y + dy[j] * i >= m) return 0;
            if (a[x + dx[j] * i][y + dy[j] * i] != '2') return 0;
        }
    }
    return 1;
}

int main() {
    int T; scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++ i) scanf("%s", a[i]);
        int ret = 0, s = 0;
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < m; ++ j) {
                if (a[i][j] != '1') continue;
                dfs(i, j, s = 0);
                if (s % 4 || s / 4 > n || s / 4 > m) continue;
                ret += check(i, j, s / 4, 0, 2) && check(i + s / 4, j + s / 4, s / 4, 2, 4);
                ret += check(i, j, s / 4, 4, 6) && check(i + s / 2, j, s / 4, 6, 8);
            }
        }
        printf("%d\n", ret);
    }
}
