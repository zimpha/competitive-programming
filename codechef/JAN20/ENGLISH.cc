#include <cstdio>
#include <string>
#include <map>
#include <functional>
#include <iostream>

using uint64 = unsigned long long;

const int N = 1e5 + 10;

struct Node {
  std::map<int, Node*> go;
  int size;
} pool[N], *ptr;

Node* new_node() {
  ptr->go.clear();
  ptr->size = 0;
  return ptr++;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int T;
  std::cin >> T;
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    std::cin >> n;
    ptr = pool;
    auto root = new_node();
    for (int i = 0; i < n; ++i) {
      std::string s;
      std::cin >> s;
      int l = s.size();
      auto p = root;
      for (int j = 0; j < l; ++j) {
        int u = (s[j] - 'a') * 26 + s[l - 1 - j] - 'a';
        if (!p->go.count(u)) p->go[u] = new_node();
        p = p->go[u];
      }
      p->size++;
    }

    uint64 ret = 0;

    std::function<int(Node*, int)> dfs = [&](Node *o, int d) {
      int cnt = o->size;
      for (auto &e: o->go) {
        cnt += dfs(e.second, d + 1);
      }
      ret += uint64(cnt / 2) * d * d;
      return cnt & 1;
    };

    dfs(root, 0);
    printf("%llu\n", ret);
  }
  return 0;
}
