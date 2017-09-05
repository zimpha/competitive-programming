#include <bits/stdc++.h>
using namespace std;

int main() {
    int Y, W; cin >> Y >> W;
    int A = 7 - max(Y, W), B = 6;
    int g = __gcd(A, B);
    A /= g, B /= g;
    cout << A << "/" << B << endl;
    return 0;
}
