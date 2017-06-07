#include "asteroids.h"
#include <message.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using ll = long long;

const int master_node = 0;
const int sending_node = -1;
const int inf = 1e9;

void brute_force(int m, int n) {
  std::vector<int> f(m, 0), g(m);
  std::vector<char> row(m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      row[j] = GetPosition(i, j);
      if (row[j] == '#') f[j] = -1;
      else if (f[j] != -1) f[j] += row[j] - '0';
    }
    g = f;
    for (int j = 0; j < m; ++j) {
      if (row[j] == '#') continue;
      if (j && f[j - 1] != -1) {
        g[j] = std::max(g[j], f[j - 1] + row[j] - '0');
      }
      if (j + 1 < m && f[j + 1] != -1) {
        g[j] = std::max(g[j], f[j + 1] + row[j] - '0');
      }
    }
    f.swap(g);
  }
  printf("%d\n", *std::max_element(f.begin(), f.end()));
}

int main() {
  int width = GetWidth();
  int height = GetHeight();
  int me = MyNodeId();
  int nodes = NumberOfNodes();
  const int min_width = 300;
  if (width < min_width) {
    if (me != 0) return 0;
    brute_force(width, height);
    return 0;
  }
  nodes = std::min<int>(width / min_width, nodes);
  if (me >= nodes) return 0;
  int L = 1ll * width * me / nodes, R = 1ll * width * (me + 1) / nodes;
  int nl = std::max(0, L - min_width), nr = std::min(width, R + min_width);
  std::vector<int> f(nr - nl), g(nr - nl);
  std::vector<char> row(nr - nl);
  for (int it = 0; it < height; it += min_width) {
    int hr = std::min(it + min_width, height);
    for (int i = hr - it; i > 0; --i) {
      int x = hr - i;
      for (int y = std::max(nl, L - i); y < std::min(nr, R + i); ++y) {
        char c = (row[y - nl] = GetPosition(x, y));
        if (c == '#') f[y - nl] = -1;
        else if (f[y - nl] != -1) f[y - nl] += c - '0';
      }
      g = f;
      for (int y = std::max(nl, L - i); y < std::min(nr, R + i); ++y) {
        char c = row[y - nl];
        if (c == '#') continue;
        if (y > nl && f[y - nl - 1] != -1) {
          g[y - nl] = std::max(g[y - nl], f[y - nl - 1] + c - '0');
        }
        if (y + 1 < nr && f[y - nl + 1] != -1) {
          g[y - nl] = std::max(g[y - nl], f[y - nl + 1] + c - '0');
        }
      }
      f.swap(g);
    }
    if (hr == height) break;
    if (me > 0) {
      for (int i = L; i < L + min_width; ++i) {
        PutInt(me - 1, f[i - nl]);
      }
      Send(me - 1);
    }
    if (me < nodes - 1) {
      for (int i = R - min_width; i < R; ++i) {
        PutInt(me + 1, f[i - nl]);
      }
      Send(me + 1);
    }
    if (me > 0) {
      Receive(me - 1);
      for (int i = L - min_width; i < L; ++i) {
        f[i - nl] = GetInt(me - 1);
      }
    }
    if (me < nodes - 1) {
      Receive(me + 1);
      for (int i = R; i < R + min_width; ++i) {
        f[i - nl] = GetInt(me + 1);
      }
    }
  }
  int ret = -1;
  for (int i = L; i < R; ++i) ret = std::max(ret, f[i - nl]);
  if (me != master_node) {
    PutInt(master_node, ret);
    Send(master_node);
  } else {
    for (int i = 1; i < nodes; ++i) {
      Receive(i);
      ret = std::max(ret, GetInt(i));
    }
    printf("%d\n", ret);
  }
  return 0;
}
