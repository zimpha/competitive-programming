#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <functional>

using int64 = long long;

struct Node {
  Node *l, *r;
  int64 value, sum;
  int size;
  Node() {}
  Node(int64 v): l(0), r(0), value(v), sum(v), size(1) {}
  Node* update() {
    size = 1;
    sum = value;
    if (l) size += l->size, sum += l->sum;
    if (r) size += r->size, sum += r->sum;
    return this;
  }
};

int get_size(Node *o) {
  return o ? o->size : 0;
}

int64 get_sum(Node *o) {
  return o ? o->sum : 0;
}

bool random(int a, int b) {
  return rand() % (a + b) < a;
}

std::pair<Node*, Node*> split_by_value(Node *o, int64 v) {//[-inf, v), [v, +inf)
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  if (o->value < v) {
    std::tie(o->r, r) = split_by_value(o->r, v);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_value(o->l, v);
    r = o;
  }
  o->update();
  return {l, r};
}

std::pair<Node*, Node*> split_by_size(Node *o, int size) {//[0, size), [size, +inf)
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  int ls = get_size(o->l);
  if (ls < size) {
    std::tie(o->r, r) = split_by_size(o->r, size - ls - 1);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_size(o->l, size);
    r = o;
  }
  o->update();
  return {l, r};
}

std::pair<Node*, Node*> split_by_sum(Node *o, int64 sum) { //[0, sum), [sum, inf)
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  int64 ls = get_sum(o->l);
  if (ls + o->value < sum) {
    std::tie(o->r, r) = split_by_sum(o->r, sum - ls - o->value);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_sum(o->l, sum);
    r = o;
  }
  o->update();
  return {l, r};
}

Node* merge(Node *l, Node *r) {
  if (!l || !r) return l ? l : r;
  if (random(l->size, r->size)) {
    l->r = merge(l->r, r);
    return l->update();
  } else {
    r->l = merge(l, r->l);
    return r->update();
  }
}

Node* kth(Node *o, int k) {
  int cnt = get_size(o->l);
  if (cnt + 1 == k) return o;
  if (k <= cnt) return kth(o->l, k);
  else return kth(o->r, k - cnt - 1);
}

const int N = 3e5 + 10, M = 2000;

int64 weight[N];
Node pool[N * 2];
int64 bound[M];
Node* buf[M];
Node* ptr;

Node* build(int l, int r) {
  if (l > r) return NULL;
  int m = (l + r) >> 1;
  Node* p = ptr++;
  p->l = build(l, m - 1);
  p->r = build(m + 1, r);
  p->value = weight[m];
  return p->update();
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
  inline int64 nextULong() {
    int c = nextChar();
    int64 x = 0;
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
  srand(time(NULL));
  int n = io.nextUInt();
  for (int i = 0; i < n; ++i) weight[i] = io.nextULong();
  std::sort(weight, weight + n);
  ptr = pool;
  auto root = build(0, n - 1);
  int m = io.nextUInt();
  for (int i = 0; i < m; ++i) {
    int op = io.nextUInt();
    if (op == 1) {
      int64 s = io.nextULong();
      int64 k = io.nextULong();
      int ts = 0, ret = 0;
      while (s < k) {
        Node *a = 0, *b = 0, *c = 0;
        std::tie(b, c) = split_by_value(root, s);
        int64 total = get_sum(b);
        int64 next = k;
        if (c) next = std::min(k, kth(c, 1)->value + 1);
        if (total + s < next) {
          root = merge(b, c);
          ret = -1;
          break;
        } else {
          int64 delta = next - s;
          std::tie(a, b) = split_by_sum(b, total + 1 - delta);
          assert(get_sum(b) >= delta);
        }
        buf[ts] = b;
        bound[ts++] = s;
        root = merge(a, c);
        s += get_sum(b);
        ret += get_size(b);
      }
      for (; ts > 0; --ts) {
        Node *o = buf[ts - 1];
        Node *a, *b;
        std::tie(a, b) = split_by_value(root, bound[ts - 1]);
        root = merge(a, merge(o, b));
      }
      printf("%d\n", ret);
    } else if (op == 2) {
      int64 w = io.nextULong();
      Node *a, *b;
      std::tie(a, b) = split_by_value(root, w);
      Node *o = ptr++;
      o->l = o->r = NULL;
      o->size = 1;
      o->value = o->sum = w;
      if (get_size(a) < get_size(b)) root = merge(merge(a, o), b);
      else root = merge(a, merge(o, b));
    } else if (op == 3) {
      int64 w = io.nextULong();
      Node *a, *b, *c;
      std::tie(a, b) = split_by_value(root, w);
      std::tie(b, c) = split_by_size(b, 1);
      root = merge(a, c);
    }
  }
  return 0;
}
