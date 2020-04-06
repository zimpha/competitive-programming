#include <cstdio>
#include <ctime>
#include <cstring>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>

struct Node {
  Node *l, *r;
  int size;
  int x, y;
  Node(int x, int y): l(0), r(0), size(1), x(x), y(y) {}
  Node* update() {
    size = 1;
    if (l) size += l->size;
    if (r) size += r->size;
    return this;
  }
  Node* left() { return l ? l->left() : this; }
  Node* right() { return r ? r->right() : this; }
};

int get_size(Node *o) {
  return o ? o->size : 0;
}

bool random(int a, int b) {
  return rand() % (a + b) < a;
}

template<class Compare>
std::pair<Node*, Node*> split_by_cmp(Node *o, const Compare& cmp) {
  Node *l = 0, *r = 0;
  if (!o) return {l, r};
  if (cmp(o)) {
    std::tie(o->r, r) = split_by_cmp(o->r, cmp);
    l = o;
  } else {
    std::tie(l, o->l) = split_by_cmp(o->l, cmp);
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

int main() {
  srand(time(NULL));
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n, k, q;
    scanf("%d%d", &n, &k);
    std::vector<int> c(n);
    std::vector<Node*> T(k), ls(k), rs(k), ms(k);

    std::set<std::pair<int, int>> extra;

    auto add = [&](int x, int y) {
      if (get_size(T.back())) {
        extra.emplace(x, y);
        return;
      }
      Node *o = new Node(x, y);
      int r = -1;
      for (int i = 0; i < k && r == -1; ++i) {
        Node *a, *b;
        std::tie(a, b) = split_by_cmp(T[i], [&](Node *o) {
          return o->x < x;
        });
        if (!a || a->right()->y >= y) r = i;
        T[i] = merge(a, b);
      }
      for (int i = r; i < k && o; ++i) {
        Node *a, *b, *c;
        int x = o->left()->x;
        std::tie(a, b) = split_by_cmp(T[i], [&](Node *o) {
          return o->x < x;
        });
        int y = o->right()->y;
        std::tie(b, c) = split_by_cmp(b, [&](Node *o) {
          return o->y > y;
        });
        T[i] = merge(a, merge(o, c));
        o = b;
      }
    };

    auto del = [&](int x, int y) {
      if (extra.count({x, y})) {
        extra.erase({x, y});
        return;
      }
      int r = -1;
      for (int i = 0; i < k && r == -1; ++i) {
        Node *a, *b;
        std::tie(a, b) = split_by_cmp(T[i], [&](Node *o) {
          return o->x < x;
        });
        if (b && b->left()->y == y && b->left()->x == x) r = i;
        T[i] = merge(a, b);
      }
      std::tie(ls[r], rs[r]) = split_by_cmp(T[r], [&](Node *o) {
        return o->x < x;
      });
      std::tie(ms[r], rs[r]) = split_by_size(rs[r], 1);
      for (int i = r + 1; i < k; ++i) {
        if (rs[i - 1]) {
          int x = rs[i - 1]->left()->x;
          std::tie(ls[i], rs[i]) = split_by_cmp(T[i], [&](Node *o) {
            return o->x < x;
          });
        } else {
          ls[i] = T[i];
          rs[i] = NULL;
        }
        if (ls[i - 1]) {
          int y = ls[i - 1]->right()->y;
          std::tie(ls[i], ms[i]) = split_by_cmp(ls[i], [&](Node *o) {
            return o->y > y;
          });
        } else {
          ms[i] = ls[i];
          ls[i] = NULL;
        }
      }
      for (int i = r; i < k; ++i) {
        if (i + 1 < k) T[i] = merge(ls[i], merge(ms[i + 1], rs[i]));
        else T[i] = merge(ls[i], rs[i]);
      }
      while (get_size(T.back()) == 0 && !extra.empty()) {
        int x = extra.begin()->first;
        int y = extra.begin()->second;
        extra.erase(extra.begin());
        add(x, y);
      }
    };

    for (int i = 0; i < n; ++i) {
      scanf("%d", &c[i]);
      add(i, c[i]);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
      int x, y;
      scanf("%d%d", &x, &y);
      del(x - 1, c[x - 1]);
      c[x - 1] = y;
      add(x - 1, c[x - 1]);
      int ret = 0;
      for (int i = 0; i < k; ++i) {
        if (get_size(T[i])) ++ret;
        else break;
      }
      printf("%d\n", ret);
    }
  }
  return 0;
}

