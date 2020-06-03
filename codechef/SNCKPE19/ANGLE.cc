#include <cstdio>
#include <algorithm>
#include <vector>

using int64 = long long;

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, p, q;
    scanf("%d%d%d", &n, &p, &q);
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i].first);
      a[i].second = i + 1;
    }
    std::sort(a.begin(), a.end());
    std::vector<int64> xs(n);
    for (int i = 0; i < n; ++i) xs[i] = (int64)a[i].first * a[i].first * q;
    int64 best_p = -1, best_q = -1;
    int x, y, z;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        // k <= low
        int low = std::upper_bound(xs.begin(), xs.end(), xs[i] + xs[j] - 2ll * p * a[i].first * a[j].first) - xs.begin() - 1;
        // y <= z <= x => x <= z + y - 1
        int64 add = a[i].first + a[j].first - 1;
        int k = std::upper_bound(xs.begin(), xs.end(), q * add * add) - xs.begin() - 1;
        k = std::min(k, low);
        if (k > j && a[k].first < a[i].first + a[j].first) {
          int64 u = a[i].first * a[i].first + a[j].first * a[j].first - a[k].first * a[k].first;
          int64 v = 2 * a[i].first * a[j].first;
          if (best_p == -1) best_p = u, best_q = v, y = i, z = j, x = k;
          else if (u * best_q < v * best_p) {
            best_p = u, best_q = v, y = i, z = j, x = k;
          }
        }
  //      printf("%lld %lld\n", best_p, best_q);
        // y <= x <= z  => x > z - y
        int64 delta = a[j].first - a[i].first;
        k = std::upper_bound(xs.begin(), xs.end(), int64(q) * delta * delta) - xs.begin();
        k = std::max(k, i + 1);
    //    printf("%d %d %d: ", i, j, k);
        if (k < j && k <= low) {
          k = std::min(j - 1, low);
          int64 u = a[i].first * a[i].first + a[j].first * a[j].first - a[k].first * a[k].first;
          int64 v = 2 * a[i].first * a[j].first;
          if (u * q >= v * p) {
            if (best_p == -1) best_p = u, best_q = v, y = i, z = j, x = k;
            else if (u * best_q < v * best_p) {
              best_p = u, best_q = v, y = i, z = j, x = k;
            }
          }
        }
      //  printf("%lld %lld\n", best_p, best_q);
        // x <= y <= z => x > z - y
        k = std::upper_bound(xs.begin(), xs.end(), int64(q) * delta * delta) - xs.begin();
        //printf("%d %d %d: ", i, j, k);
        if (k < i && k <= low) {
          k = std::min(i - 1, low);
          int64 u = a[i].first * a[i].first + a[j].first * a[j].first - a[k].first * a[k].first;
          int64 v = 2 * a[i].first * a[j].first;
          if (u * q >= v * p) {
            if (best_p == -1) best_p = u, best_q = v, y = i, z = j, x = k;
            else if (u * best_q < v * best_p) {
              best_p = u, best_q = v, y = i, z = j, x = k;
            }
          }
        }
        //printf("%lld %lld\n", best_p, best_q);
      }
    }
    if (best_p == -1) puts("-1");
    else printf("%d %d %d\n", a[x].second, a[y].second, a[z].second);
  }
  return 0;
}
