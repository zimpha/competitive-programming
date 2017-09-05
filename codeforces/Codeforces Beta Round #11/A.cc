#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000 + 10;
int a[MAXN], n, d;

int main() {
    cin >> n >> d;
    for (int i = 0; i < n; ++ i) cin >> a[i];
    int ret = 0;
    for (int i = 1; i < n; ++ i) {
        int delta = a[i - 1] - a[i];
        if (delta < 0) continue;
        ret += delta / d;
        a[i] += delta / d * d;
        while (a[i] <= a[i - 1]) ++ ret, a[i] += d;
    }
    cout << ret << endl;
    return 0;
}
