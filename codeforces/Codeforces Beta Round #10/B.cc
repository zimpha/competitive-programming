#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;

int sum[MAXN][MAXN];
int N, K;

bool calc(int &x, int &y, int M) {
    int xc = K / 2 + 1, yc = K / 2 + 1;
    int ret = 1e9;
    for (int i = 1; i <= K; ++ i) {
        for (int j = 0; j + M <= K; ++ j) {
            if (sum[i][j] - sum[i][j + M] == 0) {
                int cost = M * abs(i - xc);
                int a = j + 1, b = j + M;
                if (b <= yc) cost += (yc - a + yc - b) * M / 2;
                else if (a >= yc) cost += (a - yc + b - yc) * M / 2;
                else cost += (b - yc) * (b - yc + 1) / 2 + (yc - a) * (yc - a + 1) / 2;
                if (cost < ret) ret = cost, x = i, y = j;
            }
        }
    }
    if (ret == 1e9) return false;
    else return true;
}

int main() {
    cin >> N >> K;
    for (int i = 0; i < N; ++ i) {
        int M, x, y; cin >> M;
        if (calc(x, y, M)) {
            cout << x << " " << y + 1 << " " << y + M << endl;
            for (int i = y; i < y + M; ++ i) {
                for (int j = i; j >= 0; -- j) {
                    ++ sum[x][j];
                }
            }
        }
        else cout << -1 << endl;
    }
    return 0;
}
