#include <bits/stdc++.h>
using namespace std;

int n, ret;

int toDecimal(int mask) {
    int ret = 0;
    for (int i = 9; i >= 0; -- i) {
        int o = (mask >> i) & 1;
        ret = ret * 10 + o;
    }
    return ret;
}

int main() {
    cin >> n;
    for (int mask = 1; mask <= 0x200; ++ mask) {
        if (toDecimal(mask) <= n) ++ ret;
    }
    cout << ret << endl;
    return 0;
}
