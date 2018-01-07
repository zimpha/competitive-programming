#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

struct node {
  node* go[26];
  int mx;
  node() {
    memset(go, 0, sizeof(go));
    mx = 1e9;
  }
};

void ins(node *o, char *s) {
  int n = strlen(s);
  node *p = o;
  for (int i = 0; i < n; ++i) {
    p->mx = std::min(p->mx, n - i);
    int c = s[i] - 'a';
    if (!p->go[c]) p->go[c] = new node();
    p = p->go[c];
  }
  p->mx = 0;
}

char s[200];

int main() {
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int a, b, k, n, m;
    scanf("%d%d%d%d%d", &a, &b, &k, &n, &m);
    node *root = new node();
    for (int i = 0; i < n; ++i) {
      scanf("%s", s);
      ins(root, s);
    }
    std::vector<int> cost(m);
    for (int i = 0; i < m; ++i) {
      scanf("%s", s);
      node *p = root;
      int l = strlen(s);
      int ret = 1e9;
      for (int j = 0; j <= l; ++j) {
        if (!p) break;
        ret = std::min(ret, b * p->mx + a * (l - j));
        if (j == l) break;
        p = p->go[s[j] - 'a'];
      }
      cost[i] = ret;
    }
    std::sort(cost.begin(), cost.end());
    int ret = 0;
    for (int i = 0; i < k; ++i) ret += cost[i];
    printf("%d\n", ret);
  }
  return 0;
}
