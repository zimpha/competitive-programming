#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using uint64 = unsigned long long;

const int N = 1e6 + 10;

uint64 code[100];
int len[100];
char s[N], t[N];

struct AhoCorasick {
  static const int MAXL = 1e4 + 10, C = 2;
  struct node {
    node *go[C], *link;
    bool mark;
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
  void ins(const char *s) {
    node *p = rt;
    for (int i = 0; s[i]; ++i) {
      int o = s[i] - '0';
      if (!p->go[o]) p->go[o] = alloc();
      p = p->go[o];
    }
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
} ac;

int main() {
  int k;
  scanf("%d%s", &k, s);
  int n = strlen(s);
  bool has_zero = false;
  bool has_one = false;
  std::vector<int> len(k);
  ac.init();
  for (int i = 0; i < k; ++i) {
    scanf("%s", t);
    len[i] = strlen(t);
    if (len[i] == 1 && t[0] == '1') has_one = true;
    if (len[i] == 1 && t[0] == '0') has_zero = true;
    code[i] = 0;
    for (int j = 0; j < len[i]; ++j) {
      code[i] = code[i] * 2 + t[j] - '0';
    }
    std::reverse(t, t + len[i]);
    ac.ins(t);
  }
  if (!has_one && !has_zero) {
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      int o = ('A' <= s[i] && s[i] <= 'Z') ? s[i] - 'A' : 26 + s[i] - 'a';
      ret += len[o];
    }
    printf("%d\n", ret);
  } else if (has_one && has_zero) {
    puts("-1");
  } else {
    ac.build();
    auto p = ac.rt;
    bool found = false;
    int ret = 0;
    for (int i = n - 1; i >= 0; --i) {
      int o = ('A' <= s[i] && s[i] <= 'Z') ? s[i] - 'A' : 26 + s[i] - 'a';
      for (int j = 0; j < len[o]; ++j) {
        int x = code[o] >> j & 1;
        p = p->go[x];
        if (found) {
          if (has_zero) ret += code[o] >> j & 1;
          else ret += ~code[o] >> j & 1;
        }
        if (!p->mark) found = true;
      }
    }
    if (!found) puts("-1");
    else printf("%d\n", ret + 1);
  }
  return 0;
}
