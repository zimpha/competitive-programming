#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>

struct node {
  node *go[26];
  bool leaf;
} *root;

node *new_node() {
  node *p = new node;
  memset(p->go, 0, sizeof(p->go));
  p->leaf = false;
  return p;
}

void insert(const std::string &s) {
  int n = s.length();
  node *p = root;
  for (int i = 0 ; i < n; ++i) {
    int o = s[i] - 'a';
    if (!p->go[o]) p->go[o] = new_node();
    p = p->go[o];
  }
  p->leaf = true;
}

bool unlock(int o, const std::string &s) {
  node *p = root;
  int n = s.length(), i;
  for (i = o; i < n; ++i) {
    int o = s[i] - 'a';
    if (p->go[o]) p = p->go[o];
    else return false;
  }
  return p->leaf;
}

void solve(const std::string &s) {
  node *p = root;
  int n = s.length();
  for (int i = 0; i < n; ++i) {
    int o = s[i] - 'a';
    if (p->go[o]) {
      p = p->go[o];
      if (p->leaf) {
        if (unlock(i + 1, s)) {
          for (int k = 0; k <= i; ++k) putchar(s[k]);
          putchar(' ');
          for (int k = 1 + i; k < n; ++k) putchar(s[k]);
          puts("");
          return;
        }
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n, t;
  std::string str;
  std::cin >> n;
  root = new_node();
  while (n--) {
    std::cin >> str;
    insert(str);
  }
  for (std::cin >> t; t--; ) {
    std::cin >> str;
    solve(str);
  }
  return 0;
}
