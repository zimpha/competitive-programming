#include <cstdio>
#include <cassert>
#include <set>
#include <vector>
#include <bitset>

const int N = 10000 + 10;
using State = std::bitset<1000>;

struct Node {
  State A, B;
  Node *left, *right;
  Node *parent;
  int size, p;
  int get_size() {
    size = 1;
    if (left) size += left->get_size();
    if (right) size += right->get_size();
    return size;
  }
} nodes[N], ban[N];

int n, m, ns;

Node* rebuild(Node *o, const State &a, const State &b) {
  if (!o) return NULL;
  auto aa = o->A & a, bb = o->B & b;
  if (!aa.any() || !bb.any()) return NULL;
  Node *l = rebuild(o->left, a, b);
  Node *r = rebuild(o->right, a, b);
  if (!l && r) return r;
  if (!r && l) return l;
  Node* p = new Node();
  p->left = l;
  p->right = r;
  p->A = aa;
  p->B = bb;
  return p;
}

int size(Node *o) {
  if (!o) return 0;
  else return o->size;
}

Node* get_center(Node *root) {
  int bound = root->size / 3;
  while (true) {
    if (size(root->left) < bound && size(root->right) < bound) break;
    if (size(root->left) > size(root->right)) root = root->left;
    else root = root->right;
  }
  return root;
}

Node* work(Node* o) {
  if (!o) return o;
  o->get_size();
  if (o->size == 1) return o;
  auto c = get_center(o);
  if (c == o) return o;
  auto A = o->A, B = o->B;
  auto a = c->A, b = c->B;
  auto t3 = rebuild(o, A ^ a, B);
  t3 = work(t3);
  auto t4 = rebuild(o, a, B ^ b);
  t4 = work(t4);
  auto t5 = work(c);
  Node *t2, *t1;
  if (t4 && t5) {
    t2 = new Node();
    t2->A = a;
    t2->B = B;
    t2->left = t4;
    t2->right = t5;
  } else {
    t2 = t4 ? t4 : t5;
  }
  if (t2 && t3) {
    t1 = new Node();
    t1->A = A;
    t1->B = B;
    t1->left = t2;
    t1->right = t3;
  } else {
    t1 = t2 ? t2 : t3;
  }
  return t1;
}

void build(Node *u, int p) {
  if (!u) return;
  int now = ns++;
  ban[now].p = p;
  ban[now].A = u->A;
  ban[now].B = u->B;
  build(u->left, now);
  build(u->right, now);
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n * n; ++i) scanf("%*d");
  scanf("%d", &m);
  int root = -1;
  for (int i = 0; i < m; ++i) {
    int m1, m2, p;
    scanf("%d%d%d", &p, &m1, &m2);
    nodes[i].parent = nodes + p;
    if (p == i) root = i;
    for (int j = 0, x; j < m1; ++j) {
      scanf("%d", &x);
      nodes[i].A[x] = 1;
    }
    for (int j = 0, x; j < m2; ++j) {
      scanf("%d", &x);
      nodes[i].B[x] = 1;
    }
  }
  for (int i = 0; i < m; ++i) if (nodes[i].parent != nodes + i) {
    if (!nodes[i].parent->left) nodes[i].parent->left = nodes + i;
    else nodes[i].parent->right = nodes + i;
  }
  Node* ret = work(nodes + root);
  ns = 0;
  build(ret, 0);
  printf("%d\n", ns);
  for (int i = 0; i < ns; ++i) {
    printf("%d", ban[i].p);
    std::vector<int> a, b;
    for (int j = 0; j < n; ++j) {
      if (ban[i].A[j]) a.push_back(j);
      if (ban[i].B[j]) b.push_back(j);
    }
    printf(" %d %d", (int)a.size(), (int)b.size());
    for (auto &x: a) printf(" %d", x);
    for (auto &x: b) printf(" %d", x);
    puts("");
  }
  return 0;
}
