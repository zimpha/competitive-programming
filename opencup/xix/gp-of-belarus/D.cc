#include <cstdio>
#include <vector>
#include <set>
#include <functional>

using int64 = long long;

const int N = 1 << 20, P = 20;

struct Node {
  Node *l, *r;
  int64 sum;
  int ts;
  std::pair<Node*, Node*> get(int t, int t01, int t10) {
    Node* vl = l, *vr = r;
    if (t) std::swap(vl, vr);
    if (!vl && ts < t10) std::swap(vl, vr);
    else if (!vr && ts < t01) std::swap(vl, vr);
    return {vl, vr};
  }
  void set(Node *vl, Node *vr, int t) {
    if (t) std::swap(vl, vr);
    l = vl; r = vr;
    sum = 0;
    if (l) sum += l->sum;
    if (r) sum += r->sum;
  }
} pool[N];

int a[N];
std::vector<Node*> stk;
std::set<Node*> vs[P];
int mark[P], mark01[P], mark10[P];
int id;

Node* new_node() {
  if (stk.empty()) stk.push_back(new Node());
  auto p = stk.back();
  p->l = p->r = NULL;
  p->sum = 0;
  p->ts = id;
  stk.pop_back();
  return p;
}

Node* build(int l, int r, int d) {
  Node* o = new_node();
  if (l + 1 == r) {
    scanf("%lld", &o->sum);
    return o;
  }
  int m = (l + r) >> 1;
  o->l = build(l, m, d - 1);
  o->r = build(m, r, d - 1);
  vs[d].insert(o);
  o->sum = o->l->sum + o->r->sum;
  return o;
}

Node* merge(Node *a, Node *b, int d) {
  if (!a || !b) return a ? a : b;
  if (d == 0) {
    a->sum += b->sum;
    stk.push_back(b);
    return a;
  }
  Node *al, *ar, *bl, *br;
  std::tie(al, ar) = a->get(mark[d], mark01[d], mark10[d]);
  std::tie(bl, br) = b->get(mark[d], mark01[d], mark10[d]);
  auto vl = merge(al, bl, d - 1);
  auto vr = merge(ar, br, d - 1);
  if (bl && br) vs[d].erase(b);
  stk.push_back(b);
  if (!(al && ar) && vl && vr) vs[d].insert(a);
  a->set(vl, vr, mark[d]);
  return a;
}

void add(Node *o, int d, int x, int v) {
  if (d == 0) { o->sum += v; return; }
  int xo = x >> (d - 1) & 1;
  Node *vl, *vr;
  std::tie(vl, vr) = o->get(mark[d], mark01[d], mark10[d]);
  if (xo == 0) {
    if (!vl) vl = new_node();
    add(vl, d - 1, x, v);
  } else {
    if (!vr) vr = new_node();
    add(vr, d - 1, x, v);
  }
  if (!(o->l && o->r) && vl && vr) vs[d].insert(o);
  o->set(vl, vr, mark[d]);
}

int64 psum(Node *o, int d, int x) {
  if (!o) return 0;
  if (d == 0) return o->sum;
  int xo = x >> (d - 1) & 1;
  Node *vl, *vr;
  std::tie(vl, vr) = o->get(mark[d], mark01[d], mark10[d]);
  int64 lsum = vl ? vl->sum : 0;
  if (xo == 1) return lsum + psum(vr, d - 1, x);
  else return psum(vl, d - 1, x);
}

int main() {
  for (int i = 0; i < N; ++i) stk.push_back(pool + i);
  int p, q;
  scanf("%d%d", &p, &q);
  Node *root = build(0, 1 << p, p);
  for (int i = 0; i < q; ++i) {
    id++;
    char op[10];
    int x, y;
    scanf("%s", op);
    Node *vl, *vr;
    if (op[0] == 's') { // sum
      scanf("%d%d", &x, &y);
      auto ret = psum(root, p, y);
      if (x) ret -= psum(root, p, x - 1);
      printf("%lld\n", ret);
    } else if (op[0] == 'o') { // or
      scanf("%d", &x);
      for (int d = 0; d < p; ++d) if (x >> d & 1) {
        for (auto &o: vs[d + 1]) {
          std::tie(vl, vr) = o->get(mark[d + 1], mark01[d + 1], mark10[d + 1]);
          auto v = merge(vl, vr, d);
          o->set(NULL, v, mark[d + 1]);
        }
        mark01[d + 1] = id; mark10[d + 1] = 0;
        vs[d + 1].clear();
      }
    } else if (op[0] == 'x') { // xor
      scanf("%d", &x);
      for (int d = 0; d < p; ++d) if (x >> d & 1) {
        mark[d + 1] ^= 1;
        std::swap(mark01[d + 1], mark10[d + 1]);
      }
    } else if (op[1] == 'n') { // and
      scanf("%d", &x);
      for (int d = 0; d < p; ++d) if (~x >> d & 1) {
        for (auto &o: vs[d + 1]) {
          std::tie(vl, vr) = o->get(mark[d + 1], mark01[d + 1], mark10[d + 1]);
          auto v = merge(vl, vr, d);
          o->set(v, NULL, mark[d + 1]);
        }
        mark10[d + 1] = id; mark01[d + 1] = 0;
        vs[d + 1].clear();
      }
    } else { // add
      scanf("%d%d", &x, &y);
      add(root, p, x, y);
    }
  }
  return 0;
}
