#include <cstdio>
#include <vector>
#include <algorithm>

struct FastIO {
  static const int S = 6553600;
  char buf[S];
  char wbuf[S];
  int wpos;
  int pos, len;
  bool eof;
  FILE *in;
  FastIO(FILE *_in = stdin) {
    in = _in;
    pos = len = 0;
    wpos = 0;
    eof = false;
  }
  ~FastIO() {
    flush();
  }
  void flush() {
    if (wpos) {
      fwrite(wbuf, 1, wpos, stdout);
      wpos = 0;
    }
  }
  void wchar(char c) {
    wbuf[wpos++] = c;
    if (wpos == S) flush();
  }
  void wuint(unsigned int x) {
    static char s[20];
    int m = 0;
    do {
      s[m++] = x % 10 + '0';
      x /= 10;
    } while (x);
    for (int i = m - 1; i >= 0; --i) wchar(s[i]);
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

using int64 = long long;
using uint64 = unsigned long long;
using uint32 = unsigned int;

class SchieberVishkinLCA {
public:
  // order[]: preorder of the vertex in the tree
  // parents[]: direct parent of vertex
  // root: root of the tree
  void build(int n, int order[], int parents[], int root) {
    indices.resize(n);
    ascendant.resize(n);
    head.resize(n);

    for (int i = 0; i < n; ++i) indices[order[i]] = i + 1;
    inlabel.assign(indices.begin(), indices.end());
    for (int i = n - 1; i > 0; --i) {
      int v = order[i], p = parents[v];
      if (lowbit(inlabel[p]) < lowbit(inlabel[v])) {
        inlabel[p] = inlabel[v];
      }
    }

    ascendant[root] = 0;
    for (int i = 1; i < n; ++i) {
      int v = order[i], p = parents[v];
      ascendant[v] = ascendant[p] | lowbit(inlabel[v]);
    }

    head[0] = root;
    for (int i = 1; i < n; ++i) {
      int v = order[i], p = parents[v];
      if (inlabel[v] != inlabel[p]) head[indices[v] - 1] = p;
      else head[indices[v] - 1] = head[indices[p] - 1];
    }
  }

  // return the LCA of u and v in O(1)
  int query(int u, int v) const {
    uint Iv = inlabel[v], Iu = inlabel[u];
    uint hIv = lowbit(Iv), hIu = lowbit(Iu);
    uint mask = highbit((Iv ^ Iu) | hIv | hIu);
    uint j = lowbit(ascendant[v] & ascendant[u] & ~mask);
    int x, y;
    if (j == hIv) x = v;
    else {
      mask = highbit(ascendant[v] & (j - 1));
      x = head[(indices[v] & ~mask | (mask + 1)) - 1];
    }
    if (j == hIu) y = u;
    else {
      mask = highbit(ascendant[u] & (j - 1));
      y = head[(indices[u] & ~mask | (mask + 1)) - 1];
    }
    return indices[x] < indices[y] ? x : y;
  }

private:
  using uint = unsigned int;
  static uint lowbit(uint x) { return x & (~x + 1); }
  static uint highbit(uint x) {
    x |= x >> 1; x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16;
    return x >> 1;
  }

  std::vector<uint> indices;
  std::vector<uint> inlabel;
  std::vector<uint> ascendant;
  std::vector<int> head;
} lca;

const int N = 3e5 + 10, mod = 998244353;

std::vector<int> edges[N];
uint32 sum[N][51];
int order[N], parent[N];
int dep[N], m;

void dfs(int u, int p = -1) {
  parent[u] = p;
  order[m++] = u;
  for (auto &&v: edges[u]) if (v != p) {
    dep[v] = dep[u] + 1;
    uint64 d = 1;
    for (int k = 1; k <= 50; ++k) {
      d = d * dep[v] % mod;
      sum[v][k] = d + sum[u][k];
      if (sum[v][k] >= mod) sum[v][k] -= mod;
    }
    dfs(v, u);
  }
}

int main() {
  int n = io.nextUInt();
  for (int i = 1; i < n; ++i) {
    int u = io.nextUInt() - 1;
    int v = io.nextUInt() - 1;
    edges[u].emplace_back(v);
    edges[v].emplace_back(u);
  }
  m = 0;
  dfs(0);
  lca.build(n, order, parent, 0);
  int q = io.nextUInt();
  for (int i = 0; i < q; ++i) {
    int u = io.nextUInt() - 1;
    int v = io.nextUInt() - 1;
    int k = io.nextUInt();
    int p = lca.query(u, v);
    int64 ret = (int64)sum[u][k] + sum[v][k] - sum[p][k];
    if (parent[p] != -1) ret -= sum[parent[p]][k];
    ret %= mod;
    if (ret < 0) ret += mod;
    io.wuint(ret);
    io.wchar('\n');
  }
  return 0;
}
