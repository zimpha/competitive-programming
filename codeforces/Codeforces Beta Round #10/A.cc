#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100 + 10;

int l[MAXN], r[MAXN];
int n, P1, P2, P3, T1, T2;

int cost(int t) {
    int ret = 0;
    ret += P1 * min(t, T1); t -= min(t, T1);
    ret += P2 * min(t, T2); t -= min(t, T2);
    ret += P3 * t;
    return ret;
}

int main() {
    cin >> n >> P1 >> P2 >> P3 >> T1 >> T2;
    for (int i = 0; i < n; ++ i) cin >> l[i] >> r[i];
    l[n] = r[n - 1];
    int ret = 0;
    for (int i = 0; i < n; ++ i) {
        ret += (r[i] - l[i]) * P1 + cost(l[i + 1] - r[i]);
    }
    cout << ret << endl;
    return 0;
}
