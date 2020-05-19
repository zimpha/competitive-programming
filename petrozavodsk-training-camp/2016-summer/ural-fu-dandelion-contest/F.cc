#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using int64 = long long;

struct Node {
  Node* go[2];
  int d, ty;
  bool is_end;
  int64 ways;
  Node(int d, int ty): d(d), ty(ty), is_end(false), ways(-1) {
    go[0] = go[1] = NULL;
  }
};

int64 get_ways(Node *o) {
  if (o->ways != -1) return o->ways;
  int64 ways = o->is_end;
  if (o->go[0]) ways += get_ways(o->go[0]);
  if (o->go[1]) ways += get_ways(o->go[1]);
  return o->ways = ways;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int64> pw(n + 1, 1);
  for (int i = 1; i <= n; ++i) pw[i] = 2 * pw[i - 1];
  std::vector<int64> p(m);
  for (int i = 0; i < m; ++i) scanf("%lld", &p[i]);
  if (n <= 5) {
    std::vector<std::string> s(1 << n);
    std::vector<int> sa(1 << n);
    for (int i = 0; i < (1 << n); ++i) {
      sa[i] = i;
      for (int j = i; j < (1 << n); ++j) {
        s[i].push_back('a' + __builtin_popcount(j) % 2);
      }
    }
    std::sort(sa.begin(), sa.end(), [&](int x, int y) {
      return s[x] < s[y];
    });
    for (int i = 0; i < m; ++i) {
      printf("%d%c", sa[p[i] - 1] + 1, " \n"[i == m - 1]);
    }
  } else {
    Node *root = new Node(-1, -1);
    std::vector<Node*> t0(n + 1), t1(n + 1), s0(n + 1), s1(n + 1);
    for (int i = 0; i <= n; ++i) {
      t0[i] = new Node(i, 0);
      t1[i] = new Node(i, 1);
      s0[i] = new Node(i, 2);
      s1[i] = new Node(i, 3);
    }
    root->go[0] = t0[0];
    root->go[1] = t1[0];
    t0[0]->go[0] = t1[2];
    t0[0]->go[1] = t0[1];
    t1[0]->go[0] = t1[1];
    t1[0]->go[1] = t0[2];
    for (int i = 1; i < n - 2; ++i) {
      t0[i]->go[0] = s0[i + 1];
      t0[i]->go[1] = t0[i + 1];
      t1[i]->go[0] = t1[i + 1];
      t1[i]->go[1] = s1[i + 1];
    }
    for (int i = 2; i < n - 2; ++i) {
      s0[i]->go[0] = t0[i + 1];
      s0[i]->go[1] = t1[i + 1];
      s1[i]->go[0] = t0[i + 1];
      s1[i]->go[1] = t1[i + 1];
    }
    t0[n - 2]->go[0] = t0[n - 2]->go[1] = t0[n];
    t1[n - 2]->go[0] = t1[n - 2]->go[1] = t0[n];
    s0[n - 2]->go[0] = s0[n - 2]->go[1] = t0[n];
    s1[n - 2]->go[0] = s1[n - 2]->go[1] = t0[n];
    t0[n]->is_end = true;
    for (int i = n - 2; i >= 0; --i) {
      if ((n - 2 - i) % 2 == 0) t0[i]->is_end = true;
      else t1[i]->is_end = true;
    }

    auto get_len = [&](Node *o, int e) -> int64 {
      if (o->d == -1) return 1;
      else if (o->d == 0) {
        if (o->ty == 0) return e == 0 ? 2 : 1;
        else return e == 0 ? 1 : 2;
      } else if (o->d == n - 2) {
        if (o->ty == 0) return e == 0 ? pw[o->d - 1] * 3 : pw[o->d] * 3;
        if (o->ty == 1) return e == 0 ? pw[o->d] : pw[o->d + 1];
        if (o->ty == 2) return e == 0 ? pw[o->d - 1] * 5 : pw[o->d - 2] * 3;
        if (o->ty == 3) return e == 0 ? pw[o->d - 2] * 11 : pw[o->d - 1];
      } else {
        if (o->ty == 0) return e == 0 ? pw[o->d - 1] : pw[o->d];
        if (o->ty == 1) return e == 0 ? pw[o->d] : pw[o->d - 1];
        if (o->ty == 2) return e == 0 ? pw[o->d - 1] : pw[o->d - 2] * 3;
        if (o->ty == 3) return e == 0 ? pw[o->d - 2] * 3 : pw[o->d - 1];
      }
      return -1;
    };

    get_ways(root);
    for (int i = 0; i < m; ++i) {
      Node *o = root;
      int64 w = p[i], ret = 0;
      while (true) {
        if (w == 1 && o->is_end) break;
        if (o->is_end) --w;
        if (w <= o->go[0]->ways) ret += get_len(o, 0), o = o->go[0];
        else w -= o->go[0]->ways, ret += get_len(o, 1), o = o->go[1];
      }
      ret = pw[n] - ret + 1;
      printf("%lld%c", ret, " \n"[i == m - 1]);
    }
  }
  return 0;
}
