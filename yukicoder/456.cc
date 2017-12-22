#include <bits/stdc++.h>
using namespace std;

int main() {
    int m; scanf("%d", &m);
    double e = exp(1);
    while(m--) {
        int a, b; double t; scanf("%d%d%lf", &a, &b, &t);
        if (!b) { printf("%.12f\n", pow(t, 1.0 / a)); continue; }
        if (!a) { printf("%.12f\n", exp(pow(t, 1.0 / b))); continue; }

        double q = pow(t, 1.0 / b) * a / b;
        double l = min(e, q), r = max(e, q), p;

        for (int it = 0; it < 40; ++it) {
            p = (l + r) / 2;
            (p * log(p) > q) ? r = p : l = p;
        }
        printf("%.12f\n", pow(r, (double)b / a));
    }
    return 0;
}
