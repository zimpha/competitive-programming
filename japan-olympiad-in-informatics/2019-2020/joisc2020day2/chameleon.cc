#include "chameleon.h"
#include <cstdio>
#include <cassert>
#include <vector>

const int N = 1000 + 10;
std::vector<int> edges[N];
int col[N];

void dfs(int u, int c) {
  if (col[u] != -1) return;
  col[u] = c;
  for (auto &v: edges[u]) dfs(v, c ^ 1);
}

bool check(std::vector<int> v, int x) {
  v.push_back(x);
  return Query(v) == v.size();
}

void Solve(int N) {
  for (int i = 1; i <= N * 2; ++i) {
    for (int j = 1; j < i; ++j) col[j] = -1;
    for (int j = 1; j < i; ++j) {
      if (col[j] == -1) dfs(j, 0);
    }
    std::vector<int> X, Y;
    for (int j = 1; j < i; ++j) {
      if (col[j] == 0) X.push_back(j);
      else Y.push_back(j);
    }
    for (int j = 0; j < 2; ++j) {
      while (!check(X, i)) {
        int left = 1, right = X.size();
        while (left < right) {
          int mid = (left + right - 1) >> 1;
          if (!check({X.begin(), X.begin() + mid}, i)) right = mid;
          else left = mid + 1;
        }
        edges[i].push_back(X[left - 1]);
        edges[X[left - 1]].push_back(i);
        X = {X.begin() + left, X.end()};
      }
      X.swap(Y);
    }
  }
  std::vector<int> mate(N * 2 + 1, -1);
  std::vector<int> love(N * 2 + 1, -1), loved(N * 2 + 1, -1);
  for (int i = 1; i <= N * 2; ++i) {
    if (edges[i].size() == 3) {
      int u1 = edges[i][0], u2 = edges[i][1], u3 = edges[i][2];
      int v = -1;
      if (Query({u1, u2, i}) == 1) v = u3;
      if (Query({u2, u3, i}) == 1) v = u1;
      if (Query({u3, u1, i}) == 1) v = u2;
      love[i] = v; loved[v] = i;
    } else {
      mate[i] = edges[i][0];
    }
  }
  for (int i = 1; i <= N * 2; ++i) if (edges[i].size() == 3) {
    assert(love[i] != -1 && loved[i] != -1);
    for (auto &x: edges[i]) {
      if (x != love[i] && x != loved[i]) mate[i] = x;
    }
  }
  for (int i = 1; i <= N * 2; ++i) {
    if (i < mate[i]) Answer(i, mate[i]);
  }
}
