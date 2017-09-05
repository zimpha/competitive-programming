#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 10;

int H[MAXN], L[MAXN], R[MAXN], C[MAXN], N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++ i) scanf("%d", &H[i]);
    rotate(H, max_element(H, H + N), H + N);
    H[N] = H[0];
    for (int i = N - 1; i >= 0; -- i) {
        for (R[i] = i + 1; R[i] < N && H[R[i]] < H[i]; R[i] = R[R[i]]);
        if (R[i] < N && H[R[i]] == H[i]) C[i] = C[R[i]] + 1, R[i] = R[R[i]];
    }
    long long ret = 0;
    for (int i = 0; i < N; ++ i) {
        ret += C[i];
        if (H[i] == H[0]) continue;
        for (L[i] = i - 1; L[i] > 0 && H[L[i]] <= H[i]; L[i] = L[L[i]]);
        ret += 2;
        if (L[i] == 0 && R[i] == N) -- ret;
    }
    cout << ret << endl;
    return 0;
}
