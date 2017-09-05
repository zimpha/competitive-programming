#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

int A[MAXN], B[MAXN], P[MAXN], F[MAXN], ret[MAXN];
int N, M;

int main() {
    cin >> N;
    for (int i = 1; i <= N; ++ i) cin >> A[i];
    cin >> M;
    for (int i = 1; i <= M; ++ i) cin >> B[i];
    for (int i = 1; i <= N; ++ i) {
        int best = 0;
        for (int j = 1; j <= M; ++ j) {
            if (A[i] == B[j] && F[best] + 1 > F[j]) F[j] = F[best] + 1, P[j] = best;
            else if (B[j] < A[i] && F[j] > F[best]) best = j;
        }
    }
    int best = 0, cnt = 0;
    for (int i = 1; i <= M; ++ i) {
        if (F[best] < F[i]) best = i;
    }
    for (int i = best; i; i = P[i]) ret[cnt ++] = B[i];
    cout << cnt << endl;
    for (int i = cnt - 1; i >= 0; -- i) {
        cout << ret[i] << " \n"[i == 0];
    }
    return 0;
}
