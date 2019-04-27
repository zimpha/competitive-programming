#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1000 + 10, M = 12000 + 10;

std::pair<int, int> pre[N];
int head[N], next[M], to[M], mark[M];
int in[N], out[N], state[N], sz, n;
bool found;

void dfs(int u, int d = 1) {
  state[u] = 1;
  for (int it = head[u]; ~it; it = next[it]) {
    int v = to[it];
    if (state[v] == 2) continue;
    if (state[v] == 1) {
      mark[it] = 1;
      for (int i = u; i != v; ) {
        mark[pre[i].first] = 1;
        i = pre[i].second;
      }
      found = true;
      return;
    } else {
      pre[v] = {it, u};
      dfs(v, d + 1);
      if (found) return;
    }
  }
  state[u] = 2;
}

bool find_cycle() {
  found = false;
  for (int i = 0; i < n; ++i) {
    state[i] = 0;
    pre[i] = {-1, -1};
  }
  state[n - 1] = 2;
  for (int i = 0; i < n - 1 && !found; ++i) {
    if (state[i] == 0) dfs(i);
  }
  return found;
}

void output() {
  int s = 0;
  while (head[s] != -1) {
    for (int &it = head[s]; ~it; it = next[it]) {
      if (mark[it]) continue;
      mark[it] = 1;
      printf("%d ", to[it] + 1);
      s = to[it];
      break;
    }
  }
  puts("0");
}

int main() {
  scanf("%d", &n);
  sz = 0;
  for (int i = 0; i < n; ++i) {
    int m, x;
    scanf("%d", &m);
    head[i] = -1;
    for (int j = 0; j < m; ++j) {
      scanf("%d", &x);
      --x;
      to[sz] = x;
      next[sz] = head[i];
      head[i] = sz++;
      ++in[x];
      ++out[i];
    }
  }
  if (n == 1) {
    puts("NIE");
    return 0;
  }
  bool valid = true;
  for (int i = 1; i + 1 < n; ++i) {
    valid &= in[i] == out[i];
  }
  valid &= in[0] + 1 == out[0];
  valid &= in[n - 1] == out[n - 1] + 1;
  if (!valid) {
    output();
  } else {
    if (!find_cycle()) puts("NIE");
    else {
      output();
    }
  }
  return 0;
}
