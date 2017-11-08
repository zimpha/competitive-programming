#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 110;
int f, v;
int a[maxn][maxn], dp[maxn][maxn];
int pre[maxn][maxn];

int DP() {
    dp[0][0] = 0;
    for (int i = 1; i <= f; ++ i){
        dp[i][i-1] = -100000;
    }
    for (int i = 1; i <= f; ++i){
        for (int j = i; j <= v; ++j) {
            if (dp[i][j-1] > dp[i-1][j-1] + a[i][j]) {
                dp[i][j] = dp[i][j-1];
                pre[i][j] = 0;
            }
            else {
                dp[i][j] = dp[i-1][j-1] + a[i][j];
                pre[i][j] = 1;
            }
        }
    }
    return dp[f][v]; 
}

void print(int i, int j) {
    if (j == 0) return ;
    if (pre[i][j] == 1) {
        print(i - 1, j - 1);
        if (i == f) printf("%d\n", j);
        else printf("%d ", j);
    }
    else print(i, j - 1);
} 

int main() {
    while (scanf("%d %d", &f, &v) != EOF) {
        for (int i = 1; i <= f; ++i) {
            for (int j = 1; j <= v; ++j) {
                scanf("%d", &a[i][j]);
            }
        }
        printf("%d\n", DP());
        print(f, v);
    }
    return 0;
}
