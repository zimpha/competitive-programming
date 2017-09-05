#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long LL;

const int MAXN = 5000000 + 10;
const int seed = 1e9 + 7;

LL H1[MAXN], H2[MAXN], pp[MAXN];
int F[MAXN];
char S[MAXN];

bool ispalindrome(int a, int b) {
    int len = b - a + 1;
    LL h1 = H1[a] - H1[a + len] * pp[len];
    LL h2 = H2[b] - H2[b - len] * pp[len];
    return h1 == h2;
}

int main() {
    scanf("%s", S + 1);
    int N = strlen(S + 1), ret;
    for (int i = 0; i <= N; ++ i) pp[i] = i ? pp[i - 1] * seed : 1;
    H1[N] = 0; H2[0] = 0;
    for (int i = N; i >= 1; -- i) H1[i] = H1[i + 1] * seed + S[i];
    for (int i = 1; i <= N; ++ i) H2[i] = H2[i - 1] * seed + S[i];
    F[0] = 0; ret = 0;
    for (int i = 1; i <= N; ++ i) {
        if (ispalindrome(1, i)) F[i] = F[i / 2] + 1;
        else F[i] = 0;
        ret += F[i];
    }
    printf("%d\n", ret);
    return 0;
}
