#include "stray.h"
#include <cstdio>
#include <vector>
#include <algorithm>

namespace anthony {
const int N = 20000 + 10;
const int code[6] = {0, 1, 1, 0, 1, 0};

std::vector<std::pair<int, int>> edges[N];
void dfs(int u, std::vector<int> &ret, int p, int id, int v) {
  int cnt = 0;
  for (auto &e: edges[u]) cnt += e.first != p;
  for (auto &e: edges[u]) if (e.first != p) {
    if (cnt == 1) {
      ret[e.second] = code[(id + 1) % 6];
      dfs(e.first, ret, u, (id + 1) % 6, code[(id + 1) % 6]);
    } else {
      ret[e.second] = !v;
      dfs(e.first, ret, u, v ? 0 : 1, !v);
    }
  }
}
}

std::vector<int> Mark(int n, int m, int a, int b, std::vector<int> u, std::vector<int> v) {
  using namespace anthony;
  std::vector<int> ret(m);
  if (a >= 3) {
    for (int i = 0; i < m; ++i) {
      edges[u[i]].emplace_back(v[i], i);
      edges[v[i]].emplace_back(u[i], i);
    }
    std::vector<int> dist(n, -1);
    std::vector<int> queue = {0};
    dist[0] = 0;
    for (size_t i = 0; i < queue.size(); ++i) {
      int u = queue[i];
      for (auto &e: edges[u]) if (dist[e.first] == -1) {
        dist[e.first] = dist[u] + 1;
        queue.push_back(e.first);
      }
    }
    for (int i = 0; i < m; ++i) {
      ret[i] = std::min(dist[u[i]], dist[v[i]]) % 3;
    }
  } else {
    for (int i = 0; i < m; ++i) {
      edges[u[i]].emplace_back(v[i], i);
      edges[v[i]].emplace_back(u[i], i);
    }
    dfs(0, ret, -1, 0, 0);
  }
  return ret;
}

namespace catherine {
const int N = 20000 + 10;
const int code[6] = {0, 1, 1, 0, 1, 0};

bool mark[32], found;
std::vector<int> seq;
int a, b, last;

}

void Init(int A, int B) {
  using namespace catherine;
  a = A;
  b = B;
  last = -2;
  found = false;
  seq.clear();
  for (int i = 0; i < 32; ++i) mark[i] = 0;
  for (int i = 0; i < 6; ++i) {
    int u = 0;
    for (int j = 0; j < 5; ++j) {
      u = u * 2 + code[(i + j) % 6];
    }
    mark[u] = 1;
  }
}

int Move(std::vector<int> y) {
  using namespace catherine;
  if (a >= 3) {
    if (last != -2) y[last]++;
    for (int x = 0; x < 3; ++x) {
      if (!y[x] && y[(x + 1) % 3]) {
        last = (x + 1) % 3;
        break;
      }
    }
    return last;
  }
  if (last == -2) {
    std::vector<int> u;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < y[i]; ++j) u.push_back(i);
    }
    if (u.size() == 1) {
      found = true;
      last = u.back();
      return last;
    }
    if (u.size() == 2) {
      seq = u;
      last = u.back();
      return last;
    }
    found = true;
    for (auto &x: u) y[x]++;
    if (y[0] < y[1]) last = 0;
    else last = 1;
    return last;
  } else {
    int deg = y[0] + y[1] + 1;
    if (deg == 1) {
      found = true;
      last = -1;
      return -1;
    } else if (deg > 2) {
      found = true;
      int u = last;
      y[u]++;
      if (y[0] < y[1]) last = 0;
      else last = 1;
      y[u]--;
      if (y[last] == 0) last = -1;
      return last;
    } else {
      if (found) {
        if (y[0] < y[1]) last = 1;
        else last = 0;
      } else if (seq.size() == 4) {
        if (y[0] < y[1]) seq.push_back(1);
        else seq.push_back(0);
        int u = 0;
        for (auto &x: seq) u = u * 2 + x;
        if (mark[u]) last = -1;
        else {
          if (y[0] < y[1]) last = 1;
          else last = 0;
        }
        found = true;
      } else {
        if (y[0] < y[1]) last = 1;
        else last = 0;
        seq.push_back(last);
      }
      return last;
    }
  }
}
