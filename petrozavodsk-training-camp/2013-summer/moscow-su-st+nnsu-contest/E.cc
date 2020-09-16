#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 500;

std::vector<int> edges[N];
int ws[N * N], eid[N * N], wid[N * N];
int st[N * N], sum[N];

int main() {
  freopen("roads.in", "r", stdin);
  freopen("roads.out", "w", stdout);
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edges[u - 1].push_back(i);
    edges[v - 1].push_back(i);
    ws[i] = wid[i] = w;
  }
  std::sort(ws, ws + m);
  for (int i = 0; i < m; ++i) {
    wid[i] = std::lower_bound(ws, ws + m, wid[i]) - ws;
    eid[wid[i]] = i;
  }
  for (int i = 0; i < m; ++i) {
    st[i] = 1;
    sum[i / n] += 1;
  }
  for (int i = 0; i < q; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x == 1) {
      for (auto &e: edges[y - 1]) {
        int w = wid[e];
        sum[w / n] -= st[w];
        st[w] ^= 1;
        sum[w / n] += st[w];
      }
    } else {
      int ret = -1;
      for (int b = 0, s = 0; b < m; b += n) {
        if (s + sum[b / n] >= y) {
          for (int w = b; ; ++w) {
            s += st[w];
            if (s == y) {
              ret = eid[w] + 1;
              break;
            }
          }
          break;
        }
        s += sum[b / n];
      }
      printf("%d\n", ret);
    }
  }
  return 0;
}
