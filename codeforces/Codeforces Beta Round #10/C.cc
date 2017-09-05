#include <bits/stdc++.h>
using namespace std;

int d(int n) {
    int s = 0;
    for (; n; n /= 10) {
        s += n % 10;
    }
    if (s <= 9) return s;
    else return d(s);
}

int root[10];

int main() {
    int N; cin >> N;
    for (int i = 1; i <= N; ++ i) ++ root[d(i)];
    long long ret = 0;
    for (int a = 0; a <= 9; ++ a) {
        for (int b = 0; b <= 9; ++ b) {
            ret += (long long)root[a] * root[b] * root[d(a * b)];
        }
    }
    for (int i = 1; i <= N; ++ i) ret -= N / i;
    cout << ret << endl;
    return 0;
}
