#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <algorithm>

const int N = 5e5 + 10, C = 26;

struct AhoCorasick {
  struct node {
    node *go[C], *link;
    int val;
  } pool[N], *rt;
  int sz;
  node* alloc() {
    memset(&pool[sz], 0, sizeof(pool[sz]));
    pool[sz].val = -1;
    return &pool[sz++];
  }
  void init() {
    sz = 0;
    rt = alloc();
  }
  void ins(const char *s, int val) {
    node *p = rt;
    for (int i = 0; s[i]; ++i) {
      int o = s[i] - 'a';
      if (!p->go[o]) p->go[o] = alloc();
      p = p->go[o];
    }
    p->val = val;
  }
  template<class F>
  void build(F updater) {
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
      updater(u->val, u->link->val);
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
} ac;

char s[N];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    std::vector<std::string> base(n - 1);
    ac.init();
    for (int i = 0; i < n - 1; ++i) {
      scanf("%s", s);
      base[i] = s;
      std::reverse(s, s + base[i].size());
      ac.ins(s, base[i].size());
    }
    ac.build([](int &x, int y) {
      if (y == -1) return;
      if (x == -1 || x > y) x = y;
    });
    scanf("%s", s);
    int m = strlen(s);
    std::vector<int> dp(m + 1);
    auto p = ac.rt;
    for (int i = m - 1; i >= 0; --i) {
      dp[i] = std::max(dp[i], dp[i + 1]);
      p = p->go[s[i] - 'a'];
      //printf("i=%d val=%d\n", i, p->val);
      if (p->val != -1) {
        dp[i] = std::max(dp[i], dp[i + p->val] + 1);
      }
    }
    if (dp[0] == 0) {
      puts("0");
      continue;
    }
    ac.init();
    for (int i = 0; i < n - 1; ++i) {
      ac.ins(base[i].data(), i);
    }
    ac.build([](int &x, int y) {
      if (y == -1) return;
      if (x == -1 || x < y) x = y;
    });
    std::vector<int> ed(dp[0] + 1);
    for (int i = 0; i <= m; ++i) ed[dp[i]] = i;
    std::vector<int> ret;
    for (int len = dp[0], i = 0; len; --len) {
      int best = -1, pos = -1;
      auto p = ac.rt;
      for (; i < ed[len - 1]; ++i) {
        p = p->go[s[i] - 'a'];
        if (p->val != -1) {
          if (best == -1 || best < p->val) {
            best = p->val;
            pos = i;
          }
        }
      }
      ret.push_back(best);
      i = pos + 1;
    }
    for (auto &x: ret) printf("%d ", x + 1);
    puts("");
  }
  return 0;
}
