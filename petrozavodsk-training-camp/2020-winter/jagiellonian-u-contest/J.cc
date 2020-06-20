#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <tuple>

const int N = 300000 + 10, M = 1e6 + 10;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

std::vector<int> x2y[M], y2x[M], x2z[M], z2x[M], y2z[M], z2y[M];
std::map<std::tuple<int, int, int>, int> mp;
std::tuple<int, int, int> tun[N];
int col[N];

template<int u, int v>
std::vector<int> get_adj(std::tuple<int, int, int> s) {
  std::vector<int> ret;
  for (int i = 0; i < 4; ++i) {
    std::get<u>(s) += dx[i]; std::get<v>(s) += dy[i];
    auto it = mp.find(s);
    if (it != mp.end()) ret.push_back(it->second);
    std::get<u>(s) -= dx[i]; std::get<v>(s) -= dy[i];
  }
  return ret;
}

template<int p>
int get(std::tuple<int, int, int> s) {
  std::get<p>(s) = -1;
  auto it = mp.find(s);
  if (it != mp.end()) return it->second;
  else return -1;
}

void dfs(int u, int cid) {
  col[u] = cid;
  int x, y, z;
  std::tie(x, y, z) = tun[u];

  auto extract = [&](std::vector<int> &group) {
    while (!group.empty()) {
      int v = group.back();
      group.pop_back();
      if (col[v] == -1) dfs(v, cid);
    }
  };

  std::vector<int> adj;
  if (x == -1) {
    adj = get_adj<1, 2>(tun[u]);
    extract(y2x[y - 1]); extract(y2x[y]); extract(y2x[y + 1]);
    extract(z2x[z - 1]); extract(z2x[z]); extract(z2x[z + 1]);
  } else if (y == -1) {
    adj = get_adj<0, 2>(tun[u]);
    extract(x2y[x - 1]); extract(x2y[x]); extract(x2y[x + 1]);
    extract(z2y[z - 1]); extract(z2y[z]); extract(z2y[z + 1]);
  } else if (z == -1) {
    adj = get_adj<0, 1>(tun[u]);
    extract(x2z[x - 1]); extract(x2z[x]); extract(x2z[x + 1]);
    extract(y2z[y - 1]); extract(y2z[y]); extract(y2z[y + 1]);
  }
  for (auto &v: adj) if (col[v] == -1) {
    dfs(v, cid);
  }
}

struct FastIO {
  static const int S = 655360;
  char buf[S];
  int pos, len;
  bool eof;
  FILE *in;
  FastIO(FILE *_in = stdin) {
    in = _in;
    pos = len = 0;
    eof = false;
  }
  inline int nextChar() {
    if (pos == len)
      pos = 0, len = fread(buf, 1, S, in);
    if (pos == len) {eof = true; return -1;}
    return buf[pos++];
  }
  inline int nextUInt() {
    int c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    for (;'0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x;
  }
  inline int nextInt() {
    int s = 1, c = nextChar(), x = 0;
    while (c <= 32) c = nextChar();
    if (c == '-') s = -1, c = nextChar();
    for (; '0' <= c && c <= '9'; c = nextChar()) x = x * 10 + c - '0';
    return x * s;
  }
  inline void nextString(char *s) {
    int c = nextChar();
    while (c <= 32) c = nextChar();
    for(; c > 32; c = nextChar()) *s++ = c;
    *s = 0;
  }
} io;

int main() {
  int T = io.nextUInt();
  for (int cas = 1; cas <= T; ++cas) {
    int n = io.nextUInt();
    for (int i = 0; i < M; ++i) {
      x2y[i].clear(); y2x[i].clear();
      x2z[i].clear(); z2x[i].clear();
      y2z[i].clear(); z2y[i].clear();
    }
    mp.clear();
    for (int i = 0; i < n; ++i) {
      col[i] = -1;
      int x = io.nextInt();
      int y = io.nextInt();
      int z = io.nextInt();
      tun[i] = {x, y, z};
      mp[tun[i]] = i;
      if (x == -1) {
        y2z[y].emplace_back(i);
        z2y[z].emplace_back(i);
      } else if (y == -1) {
        x2z[x].emplace_back(i);
        z2x[z].emplace_back(i);
      } else if (z == -1) {
        x2y[x].emplace_back(i);
        y2x[y].emplace_back(i);
      }
    }
    for (int i = 0, cnt = 0; i < n; ++i) if (col[i] == -1) {
      dfs(i, cnt++);
    }
    int m = io.nextUInt();
    for (int i = 0; i < m; ++i) {
      std::tuple<int, int, int> s, t;
      std::get<0>(s) = io.nextUInt();
      std::get<1>(s) = io.nextUInt();
      std::get<2>(s) = io.nextUInt();
      std::get<0>(t) = io.nextUInt();
      std::get<1>(t) = io.nextUInt();
      std::get<2>(t) = io.nextUInt();
      std::vector<int> ps = {get<0>(s), get<1>(s), get<2>(s)};
      std::vector<int> pt = {get<0>(t), get<1>(t), get<2>(t)};
      bool ret = false;
      for (auto a: ps) for (auto b: pt) {
        if (a == -1 || b == -1) continue;
        if (col[a] == col[b]) ret = true;
      }
      if (ret) puts("YES");
      else puts("NO");
    }
  }
  return 0;
}
