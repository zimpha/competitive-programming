#include <bits/stdc++.h>

const int n = 10000000;

std::vector<std::pair<int, int>> G[n / 2];

void dfs(int a, int b, int c, int d) {
    long u = a + c, v = b + d;
    long x = 2 * u * v;
    long y = u * u - v * v;
    long z = u * u + v * v;
    assert(x * x + y * y == z * z);
    if (x + y >= n / 2) return;
    if ((u ^ v) & 1) {
        for (int g = 1; g * (x + y) < n / 2; ++g) {
            G[g * x].emplace_back(z * g, y * g);
            G[g * y].emplace_back(z * g, x * g);
        }
    }
    dfs(a, b, u, v);
    dfs(u, v, c, d);
}

int main() {
    dfs(1, 0, 1, 1);
    long ret = 0;
    for (long a = 0; a < n / 2; a += 2) {
        for (auto &&v1: G[a]) {
            long c = v1.first, b = v1.second;
            for (auto &&v2: G[a / 2]) {
                long d = v2.first, h = v2.second;
                if (h >= b) continue;
                long e = sqrt((h + b) * (h + b) + a * a / 4);
                if (e * e == (h + b) * (h + b) + a * a / 4 && a + b * 2 + d * 2 <= n) {
                    ret += a + b * 2 + d * 2;
                }
            }
        }
    }
    std::cout << ret << std::endl;
    return 0;
}
