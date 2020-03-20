#include <cstdio>
#include <cstring>
#include <vector>

using int64 = long long;

const int N = 100;

char s[N][N];
int64 upp[N], low[N];
bool A[N], B[N];
int cnt_a;

namespace matroid {
bool choose[N], graph[N][N];

bool is_independent(std::vector<int64> a, int n, int &rank) {
  rank = 0;
  for (int c = 0; rank < (int)a.size() && c < n; ) {
    int p = -1;
    for (int i = rank; i < (int)a.size() && p == -1; ++i) {
      if (a[i] >> c & 1) p = i;
    }
    if (p == -1) { ++c; continue; }
    std::swap(a[rank], a[p]);
    for (int i = rank + 1; i < (int)a.size(); ++i) {
      if (a[i] >> c & 1) a[i] ^= a[rank];
    }
    ++rank; ++c;
  }
  for (auto x: a) if (x == 0) return false;
  return true;
}

std::vector<int64> build(int n) {
  std::vector<int64> a;
  for (int i = 0; i < n; ++i) {
    if (B[i] || choose[i]) a.push_back(upp[i]);
  }
  return a;
}

std::vector<int64> build_dual(int n) {
  std::vector<int64> a;
  for (int i = 0; i < n; ++i) {
    if (!B[i] && !choose[i]) a.push_back(low[i]);
  }
  return a;
}

bool aug(int n) {
  memset(graph, 0, sizeof(graph));
  std::vector<int> st, ed;
  // st: X + B + y is independent
  // ed: C - X - B - y is independent
  for (int y = 0; y < n; ++y) if (!B[y] && !choose[y]) {
    choose[y] = true;
    int rank;
    if (is_independent(build(n), n, rank)) st.push_back(y);
    is_independent(build_dual(n), n, rank);
    if (rank >= n - cnt_a) ed.push_back(y);
    choose[y] = false;
  }
  // X + B - x + y is independent
  // C - X - B + x - y is independent
  for (int x = 0; x < n; ++x) if (choose[x]) {
    choose[x] = false;
    for (int y = 0; y < n; ++y) if (!B[y] && !choose[y]) {
      choose[y] = true;
      int rank;
      if (is_independent(build(n), n, rank)) graph[x][y] = 1;
      is_independent(build_dual(n), n, rank);
      if (rank >= n - cnt_a) graph[y][x] = 1;
      choose[y] = false;
    }
    choose[x] = true;
  }
  if (st.empty() || ed.empty()) return false;
  std::vector<int> dist(n, -1), queue{st}, from(n);
  for (auto &x: st) dist[x] = 0, from[x] = -1;
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    for (int v = 0; v < n; ++v) if (graph[u][v] && dist[v] == -1) {
      dist[v] = dist[u] + 1;
      from[v] = u;
      queue.push_back(v);
    }
  }
  int best = -1;
  for (auto &x: ed) if (dist[x] != -1) {
    if (best == -1 || dist[x] < dist[best]) best = x;
  }
  for (int x = best; x != -1; x = from[x]) choose[x] ^= 1;
  return best != -1;
}
bool valid(int n) {
  int rank;
  if (!is_independent(build(n), n, rank)) return false;
  is_independent(build_dual(n), n, rank);
  return rank >= n - cnt_a;
}
}

int main() {
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  cnt_a = a;
  for (int i = 0, x; i < a; ++i) {
    scanf("%d", &x);
    A[x - 1] = true;
  }
  for (int i = 0, x; i < b; ++i) {
    scanf("%d", &x);
    B[x - 1] = true;
  }
  for (int i = 0; i < n; ++i) scanf("%s", s[i]);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (A[j]) upp[i] = (upp[i] << 1) | (s[j][i] == '1');
      else low[i] = (low[i] << 1) | (s[j][i] == '1');
    }
  }
  while (matroid::aug(n)) {
  }
  if (matroid::valid(n)) {
    std::vector<int> ret;
    for (int i = 0; i < n; ++i) {
      if (matroid::choose[i]) ret.push_back(i);
    }
    printf("%d\n", (int)ret.size());
    for (auto &x: ret) printf("%d ", x + 1);
    puts("");
  } else {
    puts("-1");
  }
  return 0;
}
