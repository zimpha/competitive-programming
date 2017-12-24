#include <cstdio>
#include <cstring>

struct node {
  node *go[26];
  int size;
  int mark;
  node() {
    memset(go, 0, sizeof(go));
    size = 0;
    mark = 0;
  }
} *root;

void insert(node *root, char *s) {
  node *p = root;
  for (int i = 0; s[i]; ++i) {
    int o = s[i] - 'a';
    p->size++;
    if (!p->go[o]) p->go[o] = new node();
    p = p->go[o];
  }
  p->size++;
  p->mark++;
}

int ask(node *root, char *s) {
  int ret = 0;
  node *p = root;
  for (int i = 0; s[i]; ++i) {
    if (!p) return ret;
    int o = s[i] - 'a';
    for (int j = 0; j < o; ++j) {
      if (p->go[j]) ret += p->go[j]->size;
    }
    p = p->go[o];
    ret += p ? p->mark : 0;
  }
  return ret;
}

const int N = 2e5;

char s[N];

int main() {
  root = new node();
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    insert(root, s);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%s", s);
    printf("%d\n", ask(root, s));
  }
  return 0;
}
