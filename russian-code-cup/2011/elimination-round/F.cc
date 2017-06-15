#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>

const int mod = 1e9 + 7;

int n, m;

struct AhoCorasick {
  static const int MAXL = 400 + 10, C = 26;
  struct node {
    node *go[C], *link;
    int dp[MAXL][21];
    bool vis[MAXL][21];
    int len;
  } pool[MAXL], *rt;
  int sz;
  node* alloc() {
    memset(&pool[sz], 0, sizeof(pool[sz]));
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
    p->len = v;
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
      u->len = std::max(u->len, u->link->len);
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
  int dfs(node *o, int i, int j) {
    if (j > 20) return 0;
    if (i == n) return j == 0;
    if (o->vis[i][j]) return o->dp[i][j];
    o->vis[i][j] = true;
    int ret = 0;
    for (int c = 0; c < 26; ++c) {
      node *u = o->go[c];
      int ni = i + 1, nj = j + 1;
      if (u->len >= nj) nj = 0;
      ret = (ret + dfs(u, ni, nj)) % mod;
    }
    return o->dp[i][j] = ret;
  }
  int solve() {
    return dfs(rt, 0, 0);
  }
} ac;

int main() {
  scanf("%d%d", &n, &m);
  ac.init();
  for (int i = 0; i < m; ++i) {
    char s[100];
    scanf("%s", s);
    ac.ins(s, strlen(s));
  }
  ac.build();
  printf("%d\n", ac.solve());
  return 0;
}
