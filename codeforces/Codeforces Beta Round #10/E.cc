#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400 + 10, inf = 2e9;

int c[MAXN], n, ret;

int main() {
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> c[i];
    ret = inf;
    for (int i = 1; i < n; ++ i) {
        for (int j = i; j < n; ++ j) {
            int sum = c[j], cnt = 1, tmp = 0, val = c[i - 1] - 1;
            for (int k = 0; k <= j; ++ k) {
                if (val < c[k]) continue;
                sum += val - val % c[k];
                cnt += val / c[k];
                val %= c[k];
            }
            val = sum;
            for (int k = 0; k < n; ++ k) {
                if (val < c[k]) continue;
                tmp += val / c[k];
                val %= c[k];
            }
            if (cnt < tmp) ret = min(ret, sum);
        }
    }
    if (ret == inf) ret = -1;
    cout << ret << endl;
    return 0;
}
