#include <bits/stdc++.h>
using namespace std;

double a, v, l, d, w;

double timeNeed(double v0, double len) {
    double tt = (v - v0) / a;
    double dd = (v + v0) * 0.5 * tt;
    if (dd > len) return (sqrt(v0 * v0 + 2.0 * a * len) - v0) / a;
    else return tt + (len - dd) / v;
}

double dist(double v0, double t) {
    double dt = (v - v0) / a;
    if (dt < t) return (v + v0) * 0.5 * dt + (t - dt) * v;
    else return v0 * t + a * t * t * 0.5;
}

int main() {
    cout.precision(18);
    cin >> a >> v >> l >> d >> w;
    if (v <= w) cout << timeNeed(0, l) << endl;
    else {
        double tw = w / a;
        double dw = dist(0, tw);
        if (dw >= d) cout << timeNeed(0, l) << endl;
        else cout << tw + 2.0 * timeNeed(w, (d - dw) * 0.5) + timeNeed(w, l - d) << endl;
    }
    return 0;
}
