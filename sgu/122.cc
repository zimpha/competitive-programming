#include <cstdio>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <functional>

const int N = 1000 + 10;

std::bitset<N> graph[N];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string line;
    if (!i) std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::stringstream sin(line);
    for (int x; sin >> x; ) {
      graph[i][x - 1] = 1;
    }
  }
  std::vector<bool> mark(n);
  std::vector<int> next(n, -1);
  std::function<void(int, int)> rev = [&](int u, int p) {
    if (u == -1) return;
    rev(next[u], u);
    next[u] = p;
  };
  auto succ = [&](int u) {
    for (int v = 0; v < n; ++v) {
      if (!mark[v] && graph[u][v]) return v;
    }
    return -1;
  };
  mark[0] = true;
  for (int cnt = 1, s = 0, t = 0; cnt < n; ) {
    if (cnt == 1) {
      for (int v; ~(v = succ(s)); s = v, ++cnt) {
        mark[v] = true;
        next[v] = s;
      }
      for (int v; ~(v = succ(t)); t = v, ++cnt) {
        mark[v] = true;
        next[t] = v;
      }
    } else {
      for (int u, v = 0; v < n; ++v) if (!mark[v]) {
        ++cnt;
        mark[v] = true;
        for (u = s; !graph[u][v]; u = next[u]);
        s = next[u];
        t = next[u] = v;
        break;
      }
    }
    if (graph[t][s]) next[t] = s;
    for (int u = next[s]; next[t] == -1; u = next[u]) {
      int v = next[u];
      if (graph[v][s] && graph[u][t]) {
        rev(v, s);
        next[u] = t;
        t = v;
      }
    }
  }
  for (int i = 0, u = 0; i < n; ++i, u = next[u]) {
    printf("%d ", u + 1);
  }
  puts("1");
  return 0;
}
