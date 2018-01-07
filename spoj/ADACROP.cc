#include <cstdio>
#include <utility>
#include <functional>
#include <vector>
#include <map>

struct node_t {
  node_t *l, *r;
  int size, value;
  node_t(int v): l(0), r(0), size(1), value(v) {}
  node_t* update() {
    size = 1;
    if (l) size += l->size;
    if (r) size += r->size;
    return this;
  }
};

int get_size(node_t *o) {
  return o ? o->size : 0;
}

bool random(int a, int b) {
  return rand() % (a + b) < a;
}

std::pair<node_t*, node_t*> split_by_value(node_t *o, int v) {//[-inf, v), [v, +inf)
  node_t *l = 0, *r = 0;
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

std::pair<node_t*, node_t*> split_by_size(node_t *o, int size) {//[0, size), [size, +inf)
  node_t *l = 0, *r = 0;
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

node_t* merge(node_t *l, node_t *r) {
  if (!l || !r) return l ? l : r;
  if (random(l->size, r->size)) {
    l->r = merge(l->r, r);
    return l->update();
  } else {
    r->l = merge(l, r->l);
    return r->update();
  }
}

int rank(node_t *o, int v) {// number elements < v
  if (!o) return 0;
  if (o->value >= v) return rank(o->l, v);
  else return get_size(o->l) + 1 + rank(o->r, v);
}

node_t* kth(node_t *o, int k) {
  int cnt = get_size(o->l);
  if (cnt + 1 == k) return o;
  if (k <= cnt) return kth(o->l, k);
  else return kth(o->r, k - cnt - 1);
}

const int N = 2e5 + 10;

node_t* root[N];
int n, q;

node_t* insert(node_t* o, int v) {
  node_t *a, *b;
  std::tie(a, b) = split_by_value(o, v);
  return merge(a, merge(new node_t(v), b));
}

node_t *remove(node_t* o, int v) {
  node_t *a, *b, *c;
  std::tie(a, b) = split_by_value(o, v);
  std::tie(b, c) = split_by_value(b, v + 1);
  return merge(a, c);
}

int main() {
  scanf("%d%d", &n, &q);
  std::map<int, node_t*> mp;
  std::vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
    mp[v[i]] = insert(mp[v[i]], i);
  }
  for (int i = 0; i < q; ++i) {
    int x, a;
    scanf("%d%d", &x, &a);
    mp[v[x]] = remove(mp[v[x]], x);
    printf("%d\n", rank(mp[a], x));
    v[x] = a;
    mp[v[x]] = insert(mp[v[x]], x);
  }
  return 0;
}
