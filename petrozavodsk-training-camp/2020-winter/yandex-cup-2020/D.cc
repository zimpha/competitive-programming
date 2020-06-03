#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 2e5 + 10, M = 2e5 + 10;

struct Edge {
  int to, next;
  bool visited;
} edges[M * 2];

char s[N];
int G[N], mark[N], deg[N];
int seq[M], sz;

void dfs(int u) {
  mark[u] = true;
  for (int &it = G[u]; ~it; ) {
    if (edges[it].visited) {
      it = edges[it].next;
      continue;
    }
    edges[it].visited = true;
    edges[it ^ 1].visited = true;
    dfs(edges[it].to);
  }
  seq[sz++] = u;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  memset(G, -1, sizeof(*G) * n);
  int root = 0;
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    edges[i * 2] = (Edge){v, G[u], false}; G[u] = i * 2;
    edges[i * 2 + 1] = (Edge){u, G[v], false}; G[v] = i * 2 + 1;
    deg[u]++; deg[v]++;
    root = u;
  }
  scanf("%s", s);
  int cnt = 0;
  for (int i = 0; i < n; ++i) cnt += deg[i] & 1;
  if (cnt) {
    puts("No");
    return 0;
  }
  dfs(root);
  for (int i = 0; i < n; ++i) if (deg[i] && !mark[i]) {
    puts("No");
    return 0;
  }
  int sum = 0, best = 0, p = 0;
  for (int i = 0; i < m; ++i) {
    if (s[seq[i]] == '(') ++sum;
    else --sum;
    if (sum < best) best = sum, p = i + 1;
  }
  if (sum != 0) puts("No");
  else {
    puts("Yes");
    std::rotate(seq, seq + p, seq + m);
    for (int i = 0; i < m; ++i) {
      printf("%d ", seq[i] + 1);
    }
    puts("");
  }
  return 0;
}
