#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#include <queue>

const int N = 128;

using state = std::bitset<N>;

int f[N][2][2][2];
char a[N], b[N];

int main() {
  int n, m, s;
  scanf("%d%d%d", &n, &m, &s);
  std::vector<std::vector<int>> edges(m);
  std::vector<state> output(m);
  std::vector<int> deg(m);
  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x > 0) edges[x - 1].push_back(i);
    else output[i][-x - 1] = output[i][-x - 1] ^ 1;
    if (y > 0) edges[y - 1].push_back(i);
    else output[i][-y - 1] = output[i][-y - 1] ^ 1;
    deg[i] = (x > 0) + (y > 0);
  }
  std::queue<int> queue;
  for (int i = 0; i < m; ++i) {
    if (deg[i] == 0) queue.push(i);
  }
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (auto &&v: edges[u]) {
      output[v] ^= output[u];
      if (--deg[v] == 0) queue.push(v);
    }
  }
  auto u = output[s - 1];
  memset(f, 0, sizeof(f));
  scanf("%s%s", a, b);
  f[0][1][1][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int ea = 0; ea < 2; ++ea) {
      for (int eb = 0; eb < 2; ++eb) {
        int l = ea ? a[i] - '0' : 0;
        int r = eb ? b[i] - '0' : 1;
        for (int o = 0; o < 2; ++o) {
          for (int x = l; x <= r; ++x) {
            if (u[i]) {
              f[i + 1][ea && x == a[i] - '0'][eb && x == b[i] - '0'][o ^ x] += f[i][ea][eb][o];
            } else {
              f[i + 1][ea && x == a[i] - '0'][eb && x == b[i] - '0'][o] += f[i][ea][eb][o];
            }
          }
        }
      }
    }
  }
  int ret = 0;
  for (int ea = 0; ea < 2; ++ea) {
    for (int eb = 0; eb < 2; ++eb) {
      ret += f[n][ea][eb][1];
    }
  }
  printf("%d\n", ret);
  return 0;
}
