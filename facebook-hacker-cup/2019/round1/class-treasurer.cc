#include <cstdio>
#include <algorithm>

using int64 = long long;

const int N = 1e6 + 10;
const int mod = 1e9 + 7;

char s[N];
int64 pw[N];

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        int n, k;
        scanf("%d%d%s", &n, &k, s);
        pw[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pw[i] = pw[i - 1] * 2 % mod;
        }
        int mx = n, cnt = 0, ret = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == 'B') {
                ++cnt;
                if (cnt * 2 + i > mx + k) {
                    ret = (ret + pw[i + 1]) % mod;
                    --cnt;
                }
                mx = std::min(mx, 2 * cnt + i);
            } else {
                mx = std::min(mx, 2 * cnt + i);
            }
        }
        printf("Case #%d: %d\n", cas, ret);
    }
    return 0;
}
