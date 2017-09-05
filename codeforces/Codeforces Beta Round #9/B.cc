#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100 + 10;

int x[MAXN], xu, yu;
int n, vb, vs;

int main() {
    cin >> n >> vb >> vs;
    for (int i = 0; i < n; ++ i) cin >> x[i];
    cin >> xu >> yu;
    double ret = 1e10, dis = 1e10;
    int pos = -1;
    for (int i = 1; i < n; ++ i) {
        double tmp = hypot(xu - x[i], yu) / (double)vs + (double)x[i] / (double)vb;
        if (tmp < ret || (tmp == ret && dis > hypot(xu - x[i], yu))) {
            ret = tmp, pos = i + 1;
            dis = hypot(xu - x[i], yu);
        }
    }
    cout << pos << endl;
    return 0;
}
