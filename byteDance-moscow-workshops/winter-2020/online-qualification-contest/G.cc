#include <cstdio>
#include <vector>
#include <algorithm>

using int64 = long long;

const int mod = 998244353;
const int N = 1e5 + 10;

struct TreeNode {
  TreeNode *l, *r;
  int64 size;
  void update() {
    size = 0;
    if (l) size += l->size;
    if (r) size += r->size;
    if (size >= mod) size -= mod;
  }
};

TreeNode* ins(TreeNode* o, int l, int r, int x, TreeNode *v) {
  if (l + 1 == r) return v;
  TreeNode *p = new TreeNode();
  if (o) *p = *o;
  int m = (l + r) >> 1;
  if (x < m) p->l = ins(p->l, l, m, x, v);
  else p->r = ins(p->r, m, r, x, v);
  p->update();
  return p;
}

TreeNode* get(TreeNode* o, int l, int r, int x) {
  if (!o || l + 1 == r) return o;
  int m = (l + r) >> 1;
  if (x < m) return get(o->l, l, m, x);
  else return get(o->r, m, r, x);
}

struct TrieNode {
  TreeNode* root;
  std::vector<int> go;
} trie[N];

std::vector<int> edges[N];
std::vector<std::vector<int>> path[N];

int main() {
  int n, m, k;
  scanf("%d%d", &n, &m);
  std::vector<int> deg(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    trie[v].go.push_back(u);
    edges[u].push_back(v);
    deg[v]++;
  }
  scanf("%d", &k);
  for (int i = 0, l; i < k; ++i) {
    scanf("%d", &l);
    std::vector<int> v(l);
    for (int j = 0; j < l; ++j) {
      scanf("%d", &v[j]);
      --v[j];
    }
    std::reverse(v.begin(), v.end());
    path[v[0]].emplace_back(std::move(v));
  }
  std::vector<int> queue;
  for (int i = 0; i < n; ++i) {
    std::sort(trie[i].go.begin(), trie[i].go.end());
    if (deg[i] == 0) queue.push_back(i);
  }
  trie[0].root = new TreeNode();
  trie[0].root->l = trie[0].root->r = NULL;
  trie[0].root->size = 1;
  std::vector<int64> ret(n);
  for (size_t i = 0; i < queue.size(); ++i) {
    int u = queue[i];
    for (auto &p: path[u]) {
      int l = p.size();
      std::vector<TreeNode*> nodes(l);
      std::vector<int> idx(l);
      TreeNode* node = trie[u].root;
      if (!node) continue;
      nodes[0] = node;
      for (int j = 1; j < l; ++j) {
        idx[j] = std::lower_bound(trie[p[j - 1]].go.begin(), trie[p[j - 1]].go.end(), p[j]) - trie[p[j - 1]].go.begin();
        node = get(node, 0, trie[p[j - 1]].go.size(), idx[j]);
        nodes[j] = node;
        if (!node) break;
      }
      if (nodes.back()) {
        nodes[l - 1] = NULL;
        for (int j = l - 1; j > 0; --j) {
          nodes[j - 1] = ins(nodes[j - 1], 0, trie[p[j - 1]].go.size(), idx[j], nodes[j]);
        }
        trie[u].root = nodes[0];
      }
    }
    ret[u] = trie[u].root ? trie[u].root->size : 0;
    for (auto &v: edges[u]) {
      auto x = std::lower_bound(trie[v].go.begin(), trie[v].go.end(), u) - trie[v].go.begin();
      trie[v].root = ins(trie[v].root, 0, trie[v].go.size(), x, trie[u].root);
      if (--deg[v] == 0) queue.push_back(v);
    }
  }
  for (int i = 1; i < n; ++i) {
    if (i > 1) putchar(' ');
    printf("%lld", ret[i]);
  }
  puts("");
  return 0;
}
