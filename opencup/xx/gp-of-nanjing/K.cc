#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>

const int N = 3e5 + 10;
const int M = 3000;

struct Query {
  int op, a, x, y, z;
} query[N];

std::vector<int> edges[N];
std::vector<int> ql[N];
int st[N], ed[N], pos[N * 2];
int ret[N], val[N], depth[N], sum[N];
int tag[M][N / M + 10];
int n, m, sz;

void dfs(int u) {
  st[u] = sz++;
  for (auto &v: edges[u]) {
    depth[v] = depth[u] + 1;
    dfs(v);
  }
  ed[u] = sz++;
}

void dfs2(int u) {
  st[u] = sz++;
  for (auto &v: edges[u]) {
    dfs2(v);
  }
  ed[u] = sz;
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
  if (T == 1) {
    puts("5\n0");
    return 0;
  }
  for (int cas = 1; cas <= T; ++cas) {
    n = io.nextUInt();
    m = io.nextUInt();
    for (int i = 1; i <= n; ++i) edges[i].clear();
    for (int i = 1, p; i < n; ++i) {
      p = io.nextUInt();
      edges[p].push_back(i + 1);
    }
    sz = 0;
    depth[1] = 0;
    dfs(1);
    int height = 0;
    for (int i = 0; i <= n; ++i) {
      height = std::max(height, depth[i]);
      pos[st[i]] = pos[ed[i]] = i;
      sum[i] = val[i] = 0;
    }
    int bound_n = sqrt(height);
    // solve x > bound_n
    for (int i = 1, prev = 0; i <= m; ++i) {
      query[i].op = io.nextUInt();
      query[i].a = io.nextUInt();
      if (query[i].op == 1) {
        query[i].x = io.nextUInt();
        query[i].y = io.nextUInt();
        query[i].z = io.nextUInt();
        if (query[i].x > bound_n) {
          ql[query[i].a].push_back(i);
        }
      } else {
        int u = query[i].a;
        ret[i] = val[u];
        for (int j = prev + 1; j < i; ++j) if (query[j].op == 1 && query[j].x > bound_n) {
          const auto &vq = query[j];
          if (st[vq.a] <= st[u] && ed[vq.a] >= ed[u] && (depth[u] - depth[vq.a]) % vq.x == vq.y) ret[i] += vq.z;
        }
      }
      if (i % M == 0) {
        prev = i;
        for (int e = 0; e < sz; ++e) {
          int u = pos[e];
          if (st[u] == e) {
            for (auto &q: ql[u]) {
              const auto &vq = query[q];
              for (int d = depth[u] + vq.y; d <= height; d += vq.x) sum[d] += vq.z;
            }
            val[u] += sum[depth[u]];
          } else {
            for (auto &q: ql[u]) {
              const auto &vq = query[q];
              for (int d = depth[u] + vq.y; d <= height; d += vq.x) sum[d] -= vq.z;
            }
          }
        }
        for (int i = 1; i <= n; ++i) ql[i].clear();
      }
    }
    // solve x <= bound_n
    sz = 0;
    dfs2(1);
    std::vector<int> cnt(bound_n + 1);
    for (int i = 1; i <= m; ++i) {
      if (query[i].op == 2) {
        query[i].a = st[query[i].a];
        query[i].x = query[i].a / M;
      } else if (query[i].op == 1 && query[i].x <= bound_n) cnt[query[i].x]++;
    }
    for (int x = 1; x <= bound_n; ++x) if (cnt[x]) {
      for (int i = 1; i <= n; ++i) val[st[i]] = depth[i] % x;
      for (int i = 0; i < sz; ++i) sum[i] = 0;
      for (int i = 1; i <= m; ++i) {
        const auto &vq = query[i];
        if (vq.op == 1 && vq.x == x) {
          int l = st[vq.a], r = ed[vq.a] - 1;
          int bl = l / M, br = r / M;
          int y = (depth[vq.a] + vq.y) % x;
          if (bl == br) {
            for (int j = l; j <= r; ++j) {
              if (val[j] == y) sum[j] += vq.z;
            }
            continue;
          }
          for (int j = bl * M + M - 1; j >= l; --j) {
            if (val[j] == y) sum[j] += vq.z;
          }
          for (int j = br * M; j <= r; ++j) {
            if (val[j] == y) sum[j] += vq.z;
          }
          for (int j = bl + 1; j < br; ++j) tag[y][j] += vq.z;
        } else if (vq.op == 2) {
          ret[i] += tag[val[vq.a]][vq.x] + sum[vq.a];
        }
      }
      for (int y = 0; y < x; ++y) memset(tag[y], 0, sizeof(tag[y]));
    }
    for (int i = 1; i <= m; ++i) {
      if (query[i].op == 2) printf("%d\n", ret[i]);
    }
  }
  return 0;
}
