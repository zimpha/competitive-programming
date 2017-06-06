#include <bits/stdc++.h>

long solve(long n) {
    long m = sqrt(n) + 10;
    std::vector<int> mu(m, 0), mark(m, 0);
    long ret = (n + 3) / 4;
    for (int i = 3; i < m; i += 2) mu[i] = -1;
    for (int i = 3; i < m; i += 2) {
        if ((i & 3) == 1 || mark[i]) {
            for (int j = i + i * 2; j < m; j += i * 2) mu[j] -= mu[i], mark[j] = 1;
            ret += (n / i / i + 3) / 4 * mu[i];
        }
    }
    return ret;
}

int main() {
    std::cout << solve(10000000) << std::endl;
    std::cout << solve(10000000000000000ll) << std::endl;
    return 0;
}
