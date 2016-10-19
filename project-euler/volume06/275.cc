#include <bits/stdc++.h>

const int N = 30, D = 15;

int mark[N * N];
int P[N], candidate[N];
int cp, cc;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

bool is_sym() {
  for (int i = 0; i < cp; ++i) {
    int x = P[i] / N, y = P[i] % N;
    if (mark[N * (N - x) + y] != 1) return false;
  }
  return true;
}

long dfs(int n, int mass, int minx, int maxx) {
  if (mass + n * (2 * minx - n - 1) / 2 > 0) return 0;
  if (mass + n * (2 * maxx + n + 1) / 2 < 0) return 0;
  if (n == 0) {
    if (mass) return 0;
    if (is_sym()) return 2;
    else return 1;
  }
  if (!cc) return 0;
  int v = candidate[--cc];
  int x = v / N, y = v % N;
  int cache = mark[v];
  // add to forbidden
  mark[v] = 2;
  long ret = dfs(n, mass, minx, maxx);
  // add to polyomino
  if (x != D) P[cp++] = v;
  mark[v] = 1;
  int top = cc;
  for (int i = 0; i < 4; ++i) {
    int xx = x + dx[i], yy = y + dy[i], vv = xx * N + yy;
    if (xx < 0 || xx >= N || yy <= 0 || mark[vv] != 0) continue;
    mark[vv] = 3;
    candidate[cc++] = vv;
  }
  minx = std::min(minx, x - D);
  maxx = std::max(maxx, x + D);
  ret += dfs(n - 1, mass + x - D, minx, maxx);
  while (cc > top) mark[candidate[--cc]] = 0;
  if (x != D) --cp;
  candidate[cc++] = v;
  mark[v] = cache;
  return ret;
}

long run(long n) {
  memset(mark, 0, sizeof(mark));
  cp = cc = 0;
  mark[D * N] = 1;
  mark[D * N + 1] = 3;
  candidate[cc++] = D * N + 1;
  return dfs(n, 0, 0, 0) / 2;
}

int main() {
  std::cout << run(6) << std::endl;
  std::cout << run(10) << std::endl;
  std::cout << run(15) << std::endl;
  std::cout << run(18) << std::endl;
  return 0;
}
