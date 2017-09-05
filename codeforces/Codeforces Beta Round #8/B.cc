#include <bits/stdc++.h>
using namespace std;

const int BIAS = 100, MAXN = 210;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {-1, 1, 0, 0};

typedef pair<int, int> PII;

char S[MAXN];
bool G[MAXN][MAXN];
int dis[MAXN][MAXN], ex, ey;
int N;

int main() {
    scanf("%s", S);
    ex = BIAS, ey = BIAS;
    N = strlen(S);
    G[BIAS][BIAS] = 1;
    for (int i = 0; i < N; ++ i) {
        if (S[i] == 'L') ex += dx[0], ey += dy[0];
        if (S[i] == 'R') ex += dx[1], ey += dy[1];
        if (S[i] == 'U') ex += dx[2], ey += dy[2];
        if (S[i] == 'D') ex += dx[3], ey += dy[3];
        G[ex][ey] = 1;
    }
    queue<PII> Q;
    memset(dis, -1, sizeof(dis));
    dis[BIAS][BIAS] = 0;
    Q.push(PII(BIAS, BIAS));
    while (!Q.empty()) {
        int x = Q.front().first, y = Q.front().second; Q.pop();
        for (int i = 0; i < 4; ++ i) {
            int xx = x + dx[i], yy = y + dy[i];
            if (G[xx][yy] && dis[xx][yy] == -1) {
                dis[xx][yy] = dis[x][y] + 1;
                Q.push(PII(xx, yy));
            }
        }
    }
    if (N == dis[ex][ey]) puts("OK");
    else puts("BUG");
    return 0;
}
