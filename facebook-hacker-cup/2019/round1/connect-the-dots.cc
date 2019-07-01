#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using int64 = long long;

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        int n, h, v;
        scanf("%d%d%d", &n, &h, &v);
        std::vector<std::pair<int64, int64>> p(n);
        int64 ax, bx, cx, dx, ay, by, cy, dy;
        scanf("%lld%lld%lld%lld%lld%lld", &p[0].first, &p[1].first, &ax, &bx, &cx, &dx);
        scanf("%lld%lld%lld%lld%lld%lld", &p[0].second, &p[1].second, &ay, &by, &cy, &dy);
        for (int i = 2; i < n; ++i) {
            p[i].first = (ax * p[i - 2].first + bx * p[i - 1].first + cx) % dx + 1;
            p[i].second = (ay * p[i - 2].second + by * p[i - 1].second + cy) % dy + 1;
        }
        std::sort(p.begin(), p.end());
        if (h + v < n) {
            printf("Case #%d: -1\n", cas);
            continue;
        }
        std::multiset<int64> rs, ls;
        std::priority_queue<int64, std::vector<int64>, std::greater<int64>> pq;
        for (int i = 0; i < n; ++i) {
            rs.insert(p[i].second);
        }
        int64 ret = -1;
        if (v >= n) ret = *rs.rbegin();
        for (int i = 0, j; i < n; i = j) {
            for (j = i; j < n && p[i].first == p[j].first; ++j) {
                rs.erase(rs.find(p[j].second));
                pq.push(p[j].second);
            }
            while (!pq.empty() && pq.size() > h) {
                ls.insert(pq.top());
                pq.pop();
            }
            if (rs.size() > v) continue;
            int64 y = 0, x = 0;
            if (!rs.empty()) y = std::max(y, *rs.rbegin());
            if (!ls.empty()) y = std::max(y, *ls.rbegin());
            if (!pq.empty()) x = p[i].first;
            if (ret == -1 || ret > x + y) {
                ret = x + y;
            }
        }
        printf("Case #%d: %lld\n", cas, ret);
    }
    return 0;
}
