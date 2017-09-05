
 #include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    if (n < 0) n = -n;
    if (n == 0) cout << "0\n";
    else {
        int sum = 0, i = 0;
        while (sum + i <= n) sum += i, ++ i;
        while (sum < n || (sum ^ n) & 1) sum += i, ++ i;
        cout << i - 1 << endl;
    }
    return 0;
}
