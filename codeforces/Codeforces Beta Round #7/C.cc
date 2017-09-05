#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

void exgcd(LL a, LL b, LL &g, LL &x, LL &y) {
    if (!b) g = a, x = 1, y = 0;
    else {
        exgcd(b, a % b, g, y, x);
        y -= x * (a / b);
    }
}

int main() {
    LL A, B, C, X, Y, G;
    cin >> A >> B >> C;
    exgcd(A, B, G, X, Y);
    if (C % G == 0) {
        LL t = -C / (A * X + B * Y);
        cout << X * t << " " << Y * t << endl;

    }
    else {
        cout << -1 << endl;
    }
}
