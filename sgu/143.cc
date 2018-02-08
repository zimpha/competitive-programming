#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 16000 + 10;

vector<int> G[MAXN];
int A[MAXN], F[MAXN];
int N, ret;

void dfs(int u, int f) {
    F[u] = A[u];
    for (int i = 0; i < (int)G[u].size(); ++ i) {
        int v = G[u][i];
        if (v == f) continue;
        dfs(v, u);
        if (F[v] > 0) F[u] += F[v];
    }
    ret = max(ret, F[u]);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++ i) {
        scanf("%d", &A[i]);
        G[i].clear();
    }
    for (int i = 1; i < N; ++ i) {
        int x, y; scanf("%d%d", &x, &y);
        G[x].push_back(y); G[y].push_back(x);
    }
    ret = -1000;
    dfs(1, 0);
    printf("%d\n", ret);
    return 0;
}
