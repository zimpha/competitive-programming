#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;

typedef pair<int, int> PII;

int H[MAXN], L[MAXN], R[MAXN], P[MAXN];
int N, K;

namespace RMQ {
    int LOG[MAXN], mx[MAXN][20];
    void build(int N, int A[]) {
        LOG[0] = -1;
        for (int i = 1; i <= N; ++ i) LOG[i] = LOG[i >> 1] + 1;
        for (int i = 0; i < N; ++ i) mx[i][0] = A[i];
        for (int j = 1; (1 << j) < N; ++ j) {
            for (int i = 0; i + (1 << j) <= N; ++ i) {
                mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int query(int a, int b) { // [a, b]
        if (a > b) swap(a, b);
        int k = LOG[b - a + 1];
        return max(mx[a][k], mx[b - (1 << k) + 1][k]);
    }
}

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; ++ i) scanf("%d", &H[i]);
    RMQ::build(N, H);
    for (int i = 0; i < N; ++ i) {
        for (P[i] = i - 1; P[i] >= 0 && H[P[i]] >= H[i]; P[i] = P[P[i]]);
        int left = P[i] + 1, right = i;
        while (left < right) {
            int mid = (left + right - 1) >> 1;
            int mx = RMQ::query(mid, i);
            if (mx - H[i] <= K) right = mid;
            else left = mid + 1;
        }
        L[i] = left;
    }
    for (int i = N - 1; i >= 0; -- i) {
        for (P[i] = i + 1; P[i] < N && H[P[i]] >= H[i]; P[i] = P[P[i]]);
        int left = i, right = P[i] - 1;
        while (left < right) {
            int mid = (left + right + 1) >> 1;
            int mx = RMQ::query(i, mid);
            if (mx - H[i] <= K) left = mid;
            else right = mid - 1;
        }
        R[i] = left;
    }
    int ret = 0;
    for (int i = 0; i < N; ++ i) ret = max(ret, R[i] - L[i] + 1);
    vector<PII> v;
    for (int i = 0; i < N; ++ i) {
        if (R[i] - L[i] + 1 == ret) v.push_back(PII(L[i] + 1, R[i] + 1));
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    cout << ret << " " << v.size() << endl;
    for (auto x : v) cout << x.first << " " << x.second << endl;
    return 0;
}
