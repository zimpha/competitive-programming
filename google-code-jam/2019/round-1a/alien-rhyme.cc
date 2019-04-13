#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

struct node {
  node* ch[26];
  int ret, size;
  bool root;
  bool mark;
  node() {
    memset(ch, 0, sizeof(ch));
    ret = 0;
    size = 0;
    root = 0;
    mark = 0;
  }
};

void ins(node* o, char *s) {
  node* p = o;
  for (int i = 0; s[i]; ++i) {
    int c = s[i] - 'A';
    p->size++;
    if (!p->ch[c]) p->ch[c] = new node();
    p = p->ch[c];
  }
  p->size++;
  p->mark = 1;
}

int solve(node *o) {
  int sum = o->mark, leaf = 1;
  for (int c = 0; c < 26; ++c) {
    if (o->ch[c]) {
      leaf = 0;
      sum += solve(o->ch[c]);
      o->ret += o->ch[c]->ret;
    }
  }
  if (sum >= 2 && !o->root) o->ret += 2, sum -= 2;
  if (leaf) return 1;
  else return sum;
}

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    node *rt = new node();
    rt->root = true;
    for (int i = 0; i < n; ++i) {
      char s[100];
      scanf("%s", s);
      int l = strlen(s);
      std::reverse(s, s + l);
      ins(rt, s);
    }
    solve(rt);
    printf("Case #%d: %d\n", cas, rt->ret);
  }
  return 0;
}
