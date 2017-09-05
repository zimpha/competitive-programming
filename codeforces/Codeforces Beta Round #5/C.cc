#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 10;

char s[MAXN];
int N, top, L[MAXN];
int ret, cnt;

void update(int i) {
    if (ret < L[i]) ret = L[i], cnt = 1;
    else if (ret == L[i]) ++ cnt;
}
int main() {
    scanf("%s", s);
    N = strlen(s); top = 0; 
    ret = 0; cnt = 1;
    for (int i = 0; i < N; ++ i) {
        if (s[i] == ')') {
            if (top) {
                -- top;
                L[top] += L[top + 1] + 2;
                update(top);
            }
            else L[0] = 0;
        }
        else ++ top, L[top] = 0;
    }
    if (ret == 0) cnt = 1;
    printf("%d %d\n", ret, cnt);
    return 0;
}
