#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <functional>

using int64 = long long;

const int N = 2000000, M = 1000000;

struct Delta {
  int delta;
  int next;
  uint8_t from;
  Delta(): delta(0) {}
} delta_pool[M];

struct Node {
  uint8_t from;
  int head;
  int next;
  int delta_head;
  int idx;
  Node(): head(-1), delta_head(-1), idx(-1) {
  }
} trie_pool[N];

int64 pw[19];
char s[100];

int main() {
  fprintf(stderr, "%d\n", int(sizeof(delta_pool) + sizeof(trie_pool)));
  pw[0] = 1;
  for (int i = 1; i < 19; ++i) {
    pw[i] = pw[i - 1] * 10;
  }
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int64> l(n), r(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld%lld", &l[i], &r[i]);
  }

  int trie_size = 0, delta_size = 0;
  int root = trie_size++;
  std::vector<int> dsu(m);

  auto go = [&] (int p, int o) {
    for (int it = trie_pool[p].head; it != -1; it = trie_pool[it].next) {
      if (trie_pool[it].from == o) return it;
    }
    return -1;
  };

  for (int i = 0; i < m; ++i) {
    scanf("%s", s);
    dsu[i] = i;
    int p = root;
    for (int j = 0; s[j]; ++j) {
      int o = s[j] - '0';
      int q = go(p, o);
      if (q == -1) {
        q = trie_size++;
        trie_pool[q].next = trie_pool[p].head;
        trie_pool[q].from = o;
        trie_pool[p].head = q;
      }
      p = q;
    }
    if (trie_pool[p].idx != -1) {
      dsu[trie_pool[p].idx] = i;
    }
    trie_pool[p].idx = i;
  }

  std::vector<int64> ret(m);
  int64 delta[20];
  memset(delta, 0, sizeof(delta));

  auto insert = [&] (char *s, int u, int len) {
    s[u] = 0;
    while (u > 1 && *s == '0') ++s, --len, --u;
    for (int i = 0; i < u; ++i) {
      int p = root;
      for (int j = i; j < u; ++j) {
        int o = s[j] - '0';
        p = go(p, o);
        if (p == -1) break;
        if (trie_pool[p].idx != -1) {
          ret[trie_pool[p].idx] += pw[len - u];
        }
      }
      if (p != -1 && len > u) {
        bool found = false;
        for (int it = trie_pool[p].delta_head; it != -1; it = delta_pool[it].next) {
          if (delta_pool[it].from == len - u) {
            delta_pool[it].delta++;
            found = true;
          }
        }
        if (!found) {
          delta_pool[delta_size].next = trie_pool[p].delta_head;
          delta_pool[delta_size].from = len - u;
          delta_pool[delta_size].delta = 1;
          trie_pool[p].delta_head = delta_size++;
        }
      }
    }
    if (len > u) {
      for (int i = 1; i <= len - u; ++i) {
        delta[i] += pw[len - u - i];
      }
    }
  };

  for (int i = 0; i < n; ++i) {
    int u = 0;
    for (int b = 18; b >= 0; --b) {
      int lo = l[i] / pw[b] % 10;
      int ro = r[i] / pw[b] % 10;
      if (lo != ro) {
        for (int k = lo + 1; k < ro; ++k) {
          s[u] = '0' + k;
          insert(s, u + 1, 19);
        }
        int v = u;
        s[v++] = '0' + ro;
        for (int j = b - 1; j >= 0; --j) {
          int o = r[i] / pw[j] % 10;
          for (int k = 0; k < o; ++k) {
            s[v] = '0' + k;
            insert(s, v + 1, 19);
          }
          s[v++] = o + '0';
        }
        insert(s, v, 19);
        v = u;
        s[v++] = lo + '0';
        for (int j = b - 1; j >= 0; --j) {
          int o = l[i] / pw[j] % 10;
          for (int k = o + 1; k < 10; ++k) {
            s[v] = '0' + k;
            insert(s, v + 1, 19);
          }
          s[v++] = o + '0';
        }
        insert(s, v, 19);
        break;
      }
      s[u++] = lo + '0';
    }
    if (l[i] == r[i]) {
      assert(u == 19);
      insert(s, u, 19);
    }
  }

  std::function<void(int)> dfs = [&](int o) {
    int64 now = delta[0];
    //for (int i = 0; i < 19; ++i) printf("%lld ", delta[i]);
    //puts("");
    int idx = trie_pool[o].idx;
    if (idx != -1) {
      for (int i = 0; i < 19; ++i) {
        ret[idx] += delta[i] * pw[i];
      }
    }
    for (int it = trie_pool[o].delta_head; it != -1; it = delta_pool[it].next) {
      delta[delta_pool[it].from] += delta_pool[it].delta;
    }
    for (int i = 0; i < 18; ++i) delta[i] = delta[i + 1];
    delta[18] = 0;
    for (int it = trie_pool[o].head; it != -1; it = trie_pool[it].next) {
      //printf("+ %d %d\n", (int)trie_pool[it].from, it);
      dfs(it);
      //printf("- %d\n", (int)trie_pool[it].from);
    }
    for (int i = 18; i > 0; --i) delta[i] = delta[i - 1];
    for (int it = trie_pool[o].delta_head; it != -1; it = delta_pool[it].next) {
      delta[delta_pool[it].from] -= delta_pool[it].delta;
    }
    delta[0] = now;
  };

  dfs(root);

  std::function<int(int)> get = [&](int x) {
    if (dsu[x] != x) dsu[x] = get(dsu[x]);
    return dsu[x];
  };

  fprintf(stderr, "%d %d\n", trie_size, delta_size);

  for (int i = 0; i < m; ++i) {
    printf("%lld\n", ret[get(i)]);
  }
  return 0;
}
