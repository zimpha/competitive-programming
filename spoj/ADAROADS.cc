#include <cstdio>
#include <algorithm>
#include <vector>

using int64 = long long;

namespace lct {
  struct node *null;
  struct node{
    node *fa, *ch[2];
    node *mx;
    int val, rev, id;
    void clr(int v) {
      fa = ch[0] = ch[1] = null;
      mx = this;
      val = v;
      rev = 0;
    }
    void upd();
    void push();
    void setc(node *p, int d) {
      ch[d] = p;
      p->fa = this;
    }
    bool d() {
      return fa->ch[1] == this;
    }
    bool isroot() {
      return fa == null || (fa->ch[0] != this && fa->ch[1] != this);
    }
    void flip() {
      if (this == null) return;
      std::swap(ch[0], ch[1]);
      rev ^= 1;
    }
    void go() {
      if (!isroot()) fa->go();
      push();
    }
    void make_root() { 
      access()->flip();
    }
    void cut() {
      access();
      ch[0]->fa = null;
      ch[0] = null;
      upd();
    }
    void rot() {
      node *f = fa, *p = fa->fa;
      int c = d(), cc = fa->d();
      f->setc(ch[!c], c);
      this->setc(f, !c);
      if (p->ch[cc] == f) p->setc(this, cc);
      else this->fa = p;
      f->upd();
    }
    node* splay() {
      for (go(); !isroot(); rot()) {
        if (!fa->isroot()) d() == fa->d() ? fa->rot() : rot();
      }
      upd();
      return this;
    }
    node* access() {
      for (node *p = this,*q = null; p != null; q = p, p = p->fa){
        p->splay()->setc(q, 1);
        p->upd();
      }
      return splay();
    }
    node* find_root() {
      node *x;
      for (x = access(); x->push(), x->ch[0] != null; x = x->ch[0]);
      return x;
    }
    void cut(node *x) {
      if (this == x || find_root() != x->find_root()) return;
      else {
        x->make_root();
        cut();
      }
    }
    void link(node *x){
      if (find_root() == x->find_root()) return;
      else {
        make_root();
        fa = x;
      }
    }
    node* get_max() {
      node *p = this;
      while (true) {
        p->push();
        if (p->val >= p->ch[0]->mx->val && p->val >= p->ch[1]->mx->val) {
          return p;
        }
        if (p->ch[0]->mx->val >= p->ch[1]->mx->val) p = p->ch[0];
        else p = p->ch[1];
      }
    }
  };
  void node::upd() {
    mx = this;
    if (ch[0]->mx->val > mx->val) mx = ch[0]->mx;
    if (ch[1]->mx->val > mx->val) mx = ch[1]->mx;
  }
  void node::push() {
    if (rev) {
      ch[0]->flip();
      ch[1]->flip();
      rev = 0;
    }
  }
  void init() {
    null = new node();
    null->clr(-1);
  }
  node* query(node *x, node *y) {
    x->make_root();
    y->access();
    return y->get_max();
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  lct::init();
  std::vector<lct::node> T(n), E(m);
  for (int i = 0; i < n; ++i) {
    T[i].clr(-1);
  }
  int64 last = 0;
  std::vector<int> x(m), y(m);
  for (int i = 0; i < m; ++i) {
    int64 a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    a ^= last;
    b ^= last;
    c ^= last;
    x[i] = a;
    y[i] = b;
    E[i].clr(c);
    E[i].id = i;
    if (T[a].find_root() == T[b].find_root()) {
      auto mx = lct::query(&T[a], &T[b]);
      if (E[i].val >= mx->val) {
        printf("%lld\n", last);
        continue;
      }
      last -= mx->val;
      mx->cut(&T[x[mx->id]]);
      mx->cut(&T[y[mx->id]]);
    }
    last += c;
    T[a].link(&E[i]);
    T[b].link(&E[i]);
    printf("%lld\n", last);
  }
  return 0;
}
