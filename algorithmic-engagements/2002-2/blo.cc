#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <stack>
#include <queue>

#include <tuple>

#define getchar getchar_unlocked
#define putchar putchar_unlocked

#define _rep(_1, _2, _3, _4, name, ...) name
#define rep2(i, n) rep3(i, 0, n)
#define rep3(i, a, b) rep4(i, a, b, 1)
#define rep4(i, a, b, c) for (int i = int(a); i < int(b); i += int(c))
#define rep(...) _rep(__VA_ARGS__, rep4, rep3, rep2, _)(__VA_ARGS__)

using namespace std;

using i64 = long long;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using f80 = long double;

int get_int() {
  int n, c, sign = 0;
  while ((c = getchar()) < '-');
  if (c == '-') sign = 1, n = 0;
  else n = c - '0';
  while ((c = getchar()) >= '0') n = n * 10 + c - '0';
  return sign ? -n : n;
}

class LinkedList {
public:
  LinkedList(int N) : N(N), next(N) { clear(); }
  void clear() { head.assign(N, -1); }
  int front(int h) { return head[h]; }
  void pop(int h) { head[h] = next[head[h]]; }
  void push(int h, int u) { next[u] = head[h], head[h] = u; }
private:
  int N;
  vector<int> next, head;
};

class DoublyLinkedList {
private:
  struct Node { int prev, next; };
public:
  DoublyLinkedList(int N) : N(N), nodes(N) { clear(); }
  void clear() { head.assign(N, -1); }
  void erase(int h, int u) {
    int pv = nodes[u].prev, nx = nodes[u].next;
    if (nx >= 0) nodes[nx].prev = pv;
    if (pv >= 0) nodes[pv].next = nx;
    else head[h] = nx;
  }
  void insert(int h, int u) {
    nodes[u] = {-1, head[h]};
    if (head[h] >= 0) nodes[head[h]].prev = u;
    head[h] = u;
  }
  template <typename Func>
  void erase_all(int first, int last, Func f) {
    for (int i = first; i <= last; ++i) {
      for (int h = head[i]; h >= 0; h = nodes[h].next) f(h);
      head[i] = -1;
    }
  }
private:
  int N;
  vector<int> head;
  vector<Node> nodes;
};

template <
  typename CapType, typename TotalCapType, bool Directed=true,
  bool UseGlobal=true, bool UseGap=true
>
class HighestLabelPushRelabel {
private:
  static constexpr TotalCapType inf = pow(10., sizeof(TotalCapType) / 4 * 9);
  struct Edge { int to, rev; CapType cap; };

public:
  struct InputEdge { int from, to; CapType cap; };
  HighestLabelPushRelabel(int N, const vector<InputEdge>& in) :
      N(N), que(N), list(N), dlist(N) {
    ofs.assign(N + 1, 0);
    for (auto& e : in) ofs[e.from + 1]++, ofs[e.to + 1]++;
    for (int i = 1; i <= N; ++i) ofs[i] += ofs[i - 1];
    edges.resize(2 * in.size());
    for (auto& e : in) add_edge(e.from, e.to, e.cap);
    for (int i = N; i > 0; --i) ofs[i] = ofs[i - 1];
    ofs[0] = 0;
  }

  TotalCapType maximum_flow(int s, int t) {
    if (s == t) return 0;
    highest_active = 0; // highest label (active)
    highest = 0; // highest label (active and inactive)
    height.assign(N, 0); height[s] = N;
    for (int i = 0; i < N; ++i) if (i != s) dlist.insert(height[i], i);
    count.assign(N, 0); count[0] = N - 1;
    excess.assign(N, 0); excess[s] = inf; excess[t] = -inf;
    for (int eid = ofs[s]; eid < ofs[s + 1]; ++eid) push(s, edges[eid]);
    global_relabel(t);
    for (int u = -1, rest = N; highest_active >= 0; ) {
      if ((u = list.front(highest_active)) < 0) { --highest_active; continue; }
      list.pop(highest_active);
      discharge(u);
      if (--rest == 0) rest = N, global_relabel(t);
    }
    return excess[t] + inf;
  }

private:
  inline void add_edge(int u, int v, CapType cap) {
    edges[ofs[u]++] = {v, ofs[v], cap};
    edges[ofs[v]++] = {u, ofs[u] - 1, Directed ? 0 : cap}; 
  }

  void global_relabel(int t) {
    if (!UseGlobal) return;
    height.assign(N, N); height[t] = 0;
    count.assign(N, 0);
    int qh = 0, qt = 0;
    for (que[qt++] = t; qh < qt; ) {
      int u = que[qh++], h = height[u] + 1;
      for (int eid = ofs[u]; eid < ofs[u + 1]; ++eid) {
        auto& e = edges[eid];
        if (height[e.to] == N && edges[e.rev].cap > 0) {
          count[height[e.to] = h] += 1;
          que[qt++] = e.to;
        }
      }
    }
    // cache
    list.clear(); dlist.clear();
    for (int u = 0; u < N; ++u) if (height[u] < N) {
      dlist.insert(height[u], u);
      if (excess[u] > 0) list.push(height[u], u);
    }
    highest = highest_active = height[que[qt - 1]];
  }

  void push(int u, Edge& e) {
    int v = e.to;
    CapType df = min(excess[u], TotalCapType(e.cap));
    e.cap -= df, edges[e.rev].cap += df;
    excess[u] -= df, excess[v] += df;
    if (0 < excess[v] && excess[v] <= df) list.push(height[v], v);
  }

  void discharge(int u) {
    int nh = N;
    for (int eid = ofs[u]; eid < ofs[u + 1]; ++eid) {
      auto& e = edges[eid];
      if (e.cap == 0) continue;
      if (height[u] == height[e.to] + 1) {
        push(u, e);
        if (excess[u] == 0) return;
      } else nh = min(nh, height[e.to] + 1);
    }
    int h = height[u];
    if (UseGap && count[h] == 1) {
      auto f = [&] (int u) { count[height[u]]--, height[u] = N; };
      dlist.erase_all(h, highest, f);
      highest = h - 1;
    } else {
      count[h]--; dlist.erase(h, u);
      height[u] = nh;
      if (nh == N) return;
      count[nh]++; dlist.insert(nh, u);
      highest = max(highest, highest_active = nh);
      list.push(nh, u);
    }
  }

  int N, highest_active, highest;
  vector<Edge> edges;
  vector<int> ofs;
  vector<int> height, count, que;
  vector<TotalCapType> excess;
  LinkedList list;
  DoublyLinkedList dlist;
};
using HLPR = HighestLabelPushRelabel<int, int64_t, true, false, true>;

#ifndef __APPLE__
  #define fread fread_unlocked
  #define fwrite fwrite_unlocked
#endif 

class IO {
  enum { E = 3, N = 1000, SIZE = 1 << 14 };
public:
  IO() : ii(SIZE), oi(0) { init(); }
  ~IO() { if (oi) flush(oi); }
  void init() {
    rep(i, N) {
      int n = i, l = 1;
      rep(j, E) num[i][E - 1 - j] = n % 10 + '0', n /= 10, l += n > 0;
      offsets[i] = E - l;
    }
  }
  char rchar() {
    if (ii == SIZE) { 
      ii = 0;
      int s = fread(in, 1, SIZE, stdin);
      if (s < SIZE) fill(in + s, in + SIZE, EOF);
    }
    return in[ii++];
  }
  int read_int() {
    char c;
    int ret = 0, sign = 0;
    while ((c = rchar()) < '-') {
      if (c == EOF) return -1;
    }
    if (c == '-') sign = 1;
    else ret = c - '0';
    while ((c = rchar()) >= '0') ret = ret * 10 + c - '0';
    return sign ? -ret : ret;
  }
  i64 read_i64() {
    char c;
    i64 ret = 0;
    while ((c = rchar()) < '0');
    ret = c - '0';
    while ((c = rchar()) >= '0') ret = ret * 10 + c - '0';
    return ret;
  }
  u32 read_u32() {
    char c;
    u32 ret = 0;
    while ((c = rchar()) < '0');
    ret = c - '0';
    while ((c = rchar()) >= '0') ret = ret * 10 + c - '0';
    return ret;
  }
  void write_u32(u32 n, bool nl=true) {
    const u32 ten9 = 1e9;
    if (n >= ten9) {
      wchar('0' + n / ten9); n %= ten9;
      u32 q = n / 1000000; n %= 1000000;
      rep(i, 3) wchar(num[q][i]);
      q = n / 1000; n %= 1000;
      rep(i, 3) wchar(num[q][i]); 
      rep(i, 3) wchar(num[n][i]);
    } else if (n >= u32(1e6)) {
      u32 q = n / 1000000; n %= 1000000;
      rep(i, offsets[q], 3) wchar(num[q][i]);
      q = n / 1000; n %= 1000;
      rep(i, 3) wchar(num[q][i]); 
      rep(i, 3) wchar(num[n][i]);
    } else if (n >= u32(1e3)) {
      u32 q = n / 1000; n %= 1000;
      rep(i, offsets[q], 3) wchar(num[q][i]);
      rep(i, 3) wchar(num[n][i]);
    } else {
      rep(i, offsets[n], 3) wchar(num[n][i]);
    }
    if (nl) wchar('\n');
  }
  void write_int(int n, bool nl=true) {
    if (n < 0) {
      n = -n;
      wchar('-');
    }
    write_u32(n, nl);
  }
  void write_u32z(u32 n) {
    u32 q = n / 1000000; n %= 1000000;
    rep(i, 3) wchar(num[q][i]);
    q = n / 1000; n %= 1000;
    rep(i, 3) wchar(num[q][i]);
    rep(i, 3) wchar(num[n][i]);
  }
  void write_u64(u64 n, bool nl=true) {
    static const u64 t18 = u64(1e18);
    static const u32 t9 = u32(1e9);
    if (n >= t18) {
      wchar('0' + n / t18); n %= t18;
      write_u32z(n / t9);
      write_u32z(n % t9);
    } else if (n >= t9) {
      write_u32(n / t9, false);
      write_u32z(n % t9);
    } else {
      write_u32(n, false);
    }
    if (nl) wchar('\n');
  }
  void write_i64(i64 n, bool nl=true) {
    if (n < 0) {
      n = -n;
      wchar('-');
    }
    write_u64(n, nl);
  }
  void wchar(char c) {
    out[oi++] = c;
    if (oi == SIZE) flush(oi);
  }
  void wstr(const char* str) {
    while (*str) wchar(*str++);
  }
  void wstr(const char* str, int len) { rep(i, len) wchar(str[i]); }
  void flush(int size) { fwrite(out, 1, size, stdout); oi = 0; }
  int ii, oi;
  int offsets[N];
  char num[N][E], in[SIZE], out[SIZE];
} io;

void solve() {
  int N = io.read_u32(), M = io.read_u32();
  vector<HLPR::InputEdge> edges(M);
  rep(i, M) {
    int u = io.read_u32() - 1, v = io.read_u32() - 1;
    edges[i] = {u, v, 1};
  }
  printf("%lld\n", HLPR(N, edges).maximum_flow(0, N - 1));
}

int main() {
  clock_t beg = clock();
  solve();
  clock_t end = clock();
  fprintf(stderr, "%.3f sec\n", double(end - beg) / CLOCKS_PER_SEC);
  return 0;
}
