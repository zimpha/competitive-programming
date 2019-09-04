#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 1e6 + 10;

std::pair<int, int> max[N], min[N];
int queue[N];

struct FastIO {
  static const int S = 1 << 20;
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
  int n = io.nextUInt();
  int m = io.nextUInt();
  for (int i = 0; i < n; ++i) {
    max[i] = min[i] = {i, -1};
  }
  for (int i = 0; i < m; ++i) {
    int a = io.nextUInt() - 1;
    int b = io.nextUInt() - 1;
    max[a] = std::max(max[a], {b, i});
    max[b] = std::max(max[b], {a, i});
    min[a] = std::min(min[a], {b, i});
    min[b] = std::min(min[b], {a, i});
  }

  int top = 0;
  for (int i = 0; i < n; ++i) {
    int x = min[i].first, y = max[i].first;
    if (x != i && top && queue[top] > x) {
      int l = 1, r = top;
      while (l < r) {
        int m = (l + r - 1) >> 1;
        if (queue[m] > x) r = m;
        else l = m + 1;
      }
      if (max[queue[l]].first > i) {
        printf("%d %d\n", min[i].second + 1, max[queue[l]].second + 1);
        return 0;
      }
    }
    if (y != i) {
      while (top && max[queue[top]].first <= y) --top;
      queue[++top] = i;
    }
  }
  puts("NIE");
  return 0;
}
