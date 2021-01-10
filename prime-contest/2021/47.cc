#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>

using int64 = long long;

struct Node {
  Node *l, *r;
  int size;
  int low, high;
  int dp, mi, mx;
  void init(int _low, int _high) {
    l = r = NULL; size = 1;
    low = _low; high = _high;
    dp = high - low;
    mi = low; mx = high;
  }
  Node* update() {
    dp = high - low;
    size = 1; mi = low; mx = high;
    if (l) {
      mi = l->mi;
      size += l->size;
      dp += l->dp + (low - l->mx + 2) / 2;
    }
    if (r) {
      size += r->size;
      dp += r->dp + (r->mi - high + 2) / 2;
      mx = r->mx;
    }
    return this;
  }
};

std::vector<Node*> pool;

Node* new_node(int low, int high) {
  Node *p;
  if (pool.empty()) p = new Node();
  else {
    p = pool.back();
    pool.pop_back();
  }
  p->init(low, high);
  return p;
}

Node* del_node(Node *o) {
  if (!o) return NULL;
  pool.push_back(o);
  del_node(o->l);
  del_node(o->r);
  return NULL;
}

int get_size(Node *o) {
  return o ? o->size : 0;
}

bool random(int a, int b) {
  return rand() % (a + b) < a;
}

// split to two parts such that: v may in the first node in the right parts
std::pair<Node*, Node*> split_by_high(Node *o, int v) {//[-inf, v), [v, +inf)
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  if (o->high + 1 < v) {
    std::tie(o->r, r) = split_by_high(o->r, v);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_high(o->l, v);
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

namespace fib {
Node* add(Node* root, int x) {
  if (x == 0) return root;
  if (x == 1) x = 2;
  Node *a, *s, *t, *b;
  std::tie(a, b) = split_by_high(root, x);
  if (!a && !b) return new_node(x, x);
  if (a) std::tie(a, s) = split_by_size(a, a->size - 1);
  else s = NULL;
  std::tie(t, b) = split_by_size(b, 1);
  // x is the most significant bit
  if (!t) {
    // check if merge with bit x - 2
    if (s->high + 2 == x) s->init(s->low, x);
    else s = merge(s, new_node(x, x));
    return merge(a, s);
  }
  bool done = false;
  if (x != t->low - 1) {
    // merge with bit x + 2
    if (t->low - 2 == x) t->init(x, t->high), done = true;
    // merge with bit x - 2
    if (s && s->high + 2 == x) s->init(s->low, x), done = true;
  }
  if (done) {
    // glue two node
    if (s && t && s->high == t->low) s->init(s->low, t->high), t = del_node(t);
    return merge(merge(a, s), merge(t, b));
  }
  a = merge(a, s);
  // single node
  if (t->low - 2 > x) {
    t = merge(new_node(x, x), t);
    return merge(a, merge(t, b));
  }
  if (x == t->high + 1) {
    // remove o->high and add x + 1
    if (t->low == t->high) t = del_node(t);
    else t->init(t->low, t->high - 2);
    return add(merge(a, merge(t, b)), x + 1);
  } else if (x % 2 != t->low % 2) {
    int nx = t->high + 1;
    if (x + 1 == t->low) t = del_node(t);
    else t->init(t->low, x - 1);
    return add(merge(a, merge(t, b)), nx);
  } else {
    int nx = t->high + 1, ny = t->low - 2;
    t->init(t->low + 1, x - 1);
    if (t->low > t->high) t = del_node(t);
    root = merge(a, merge(t, b));
    root = add(root, nx);
    return add(root, ny);
  }
}

Node* sub(Node* root, int x) {
  if (x == 0) return root;
  if (x == 1) x = 2;
  Node *a, *s, *t, *b;
  std::tie(a, b) = split_by_high(root, x + 1);
  std::tie(t, b) = split_by_size(b, 1);
  assert(t);
  if (t->low <= x && x <= t->high) {
    auto remove = [](Node *o, int x) {
      if (o->low == x) o->init(x + 2, o->high);
      else if (o->high == x) o->init(o->low, x - 2);
      else {
        Node* t = new_node(x + 2, o->high);
        o->init(o->low, x - 2);
        o = merge(o, t);
      }
      if (o->low > o->high) o = del_node(o);
      return o;
    };
    int nx = 0;
    if (x % 2 == t->low % 2) t = remove(t, x);
    else t = remove(t, x + 1), nx = x - 1;
    root = merge(a, merge(t, b));
    return add(root, nx);
  } else {
    int nx = 0, nl = 0, nr = t->low - 1;
    if (x % 2 == t->low % 2) nl = x + 1;
    else nx = x - 1, nl = x + 2;
    if (t->low + 2 > t->high) t = del_node(t);
    else t->init(t->low + 2, t->high);
    if (a) std::tie(a, s) = split_by_size(a, a->size - 1);
    else s = NULL;
    if (s && nl <= nr && s->high + 2 == nl) {
      s->init(s->low, nr);
    } else if (nl <= nr) {
      s = merge(s, new_node(nl, nr));
    }
    root = merge(merge(a, s), merge(t, b));
    return add(root, nx);
  }
}
}

int main() {
  std::vector<int64> lucas = {2, 1};
  for (int i = 2; lucas.back() <= 1e9; ++i) {
    lucas.push_back(lucas[i - 1] + lucas[i - 2]);
  }

  auto decom = [&](int n) -> std::vector<int> {
    int i = std::upper_bound(lucas.begin(), lucas.end(), n) - lucas.begin();
    std::vector<int> ret;
    for (i -= 1; i >= 2; --i) if (n >= lucas[i]) {
      ret.push_back(i);
      n -= lucas[i];
      assert(n < lucas[i]);
    }
    if (n == 1) ret.push_back(1);
    if (n == 2) ret.push_back(0);
    return ret;
  };

  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    Node* root = NULL;
    for (int i = 0; i < n; ++i) {
      int a, b, sign;
      scanf("%d%d", &a, &b);
      std::vector<int> ret;
      if (a < 0) ret = decom(-a), sign = -1;
      else ret = decom(a), sign = 1;
      std::vector<int> add, sub;
      for (auto k: ret) {
        int x = b + 1 + k, y = b + 1 - k, s = k & 1;
        add.push_back(x);
        if (y < 0) y = -y, s ^= (y + 1) & 1;
        if (s) sub.push_back(y);
        else add.push_back(y);
      }
      if (sign == -1) std::swap(add, sub);
      for (auto &x: add) root = fib::add(root, x);
      for (auto &x: sub) root = fib::sub(root, x);
      if (root->mi > 3) printf("%d\n", root->mi / 2 + root->dp);
      else if (root->size == 1) printf("%d\n", (root->high - root->low) / 2 + 1);
      else {
        Node *x, *y;
        std::tie(x, y) = split_by_size(root, 1);
        printf("%d\n", (x->high - x->low) / 2 + 1 + (y->mi - x->high + 1) / 2 + y->dp);
        root = merge(x, y);
      }
    }
    del_node(root);
  }
  return 0;
}

