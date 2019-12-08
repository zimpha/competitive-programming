#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

const int N = 4e5 + 10, M = 1e5 + 10;

struct Node {
  Node* ch[26];
  int size;
  bool mark;
} pool[N], *root, *ptr;

int cnt[M][26][26];

void ins(int n, const char *s) {
  Node* p = root;
  for (int i = 0; i < n; ++i) {
    int o = s[i] - 'a';
    p->size++;
    if (!p->ch[o]) p->ch[o] = ptr++;
    p = p->ch[o];
  }
  p->size++;
  p->mark = 1;
}

void query(int label, int n, const char *s) {
  Node* p = root;
  for (int i = 0; i < n; ++i) {
    int o = s[i] - 'a';
    for (int c = 0; c < 26; ++c) if (c != o) {
      if (p->ch[c]) cnt[label][o][c] += p->ch[c]->size;
    }
    p = p->ch[o];
    if (p->mark) cnt[label][o][o] += 1;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, q;
  std::cin >> n;
  ptr = pool;
  root = ptr++;
  std::vector<std::string> s(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> s[i];
    ins(s[i].size(), s[i].data());
  }
  for (int i = 0; i < n; ++i) {
    query(i, s[i].size(), s[i].data());
  }
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int k;
    std::string u;
    std::cin >> k >> u;
    int ret = 0;
    for (int j = 0; j < 26; ++j) {
      ret += cnt[k - 1][j][j];
      for (int t = 0; t < j; ++t) {
        ret += cnt[k - 1][u[j] - 'a'][u[t] - 'a'];
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}
