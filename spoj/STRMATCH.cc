#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

const int N = 5e5 + 10;

char s[N], t[N];
int ret[N];

struct AhoCorasick {
  static const int MAXL = 5e5 + 10, C = 26;
  struct node {
    node *go[C], *link;
    bool mark;
    int cnt;
    std::vector<node*> son;
    std::vector<int> id;
  } pool[MAXL], *rt;
  int sz;
  node* alloc() {
    memset(pool[sz].go, 0, sizeof(pool[sz].go));
    pool[sz].link = 0;
    pool[sz].mark = 0;
    pool[sz].cnt = 0;
    pool[sz].id.clear();
    pool[sz].son.clear();
    return &pool[sz++];
  }
  void init() {
    sz = 0;
    rt = alloc();
  }
  void ins(const char *s, int v) {
    node *p = rt;
    for (int i = 0; s[i]; ++i) {
      int o = s[i] - 'a';
      if (!p->go[o]) p->go[o] = alloc();
      p = p->go[o];
    }
    p->id.push_back(v);
    p->mark = true;
  }
  void build() {
    std::queue<node*> queue;
    for (int o = 0; o < C; ++o) {
      if (rt->go[o]) {
        rt->go[o]->link = rt;
        queue.push(rt->go[o]);
      } else {
        rt->go[o] = rt;
      }
    }
    for (; !queue.empty(); queue.pop()) {
      node* u = queue.front();
      u->link->son.push_back(u);
      u->mark |= u->link->mark;
      for (int o = 0; o < C; ++o) {
        if (u->go[o]) {
          u->go[o]->link = u->link->go[o];
          queue.push(u->go[o]);
        } else {
          u->go[o] = u->link->go[o];
        }
      }
    }
  }
  void find(const char *s) {
    node *p = rt;
    for (int i = 0; s[i]; ++i) {
      int o = s[i] - 'a';
      p = p->go[o];
      p->cnt++;
    }
  }
  void dfs(node *o) {
    if (!o) return;
    for (auto &&u: o->son) {
      dfs(u);
      o->cnt += u->cnt;
    }
    for (auto &&v: o->id) ret[v] = o->cnt;
  }
  void solve() {
    dfs(rt);
  }
} ac;

int main() {
  ac.init();
  int n, q;
  scanf("%d%d", &n, &q);
  scanf("%s", s);
  for (int i = 0; i < q; ++i) {
    scanf("%s", t);
    ac.ins(t, i);
  }
  ac.build();
  ac.find(s);
  ac.solve();
  for (int i = 0; i < q; ++i) {
    printf("%d\n", ret[i]);
  }
  return 0;
}
