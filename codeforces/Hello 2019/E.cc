#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <map>
#include <ctime>

using int64 = long long;

const int N = 1e5 + 10;

std::pair<int, int> u[N];
int a[N], b[N];
int dp[N], prev[N];
int s1[N], s2[N];
bool mark[N];
int max_n;

void add(int x, std::pair<int, int> v) {
  for (; x < max_n; x += ~x & x + 1) {
    u[x] = std::max(u[x], v);
  }
}

std::pair<int, int> get(int x) {
  std::pair<int, int> r = {0, -1};
  for (; x >= 0; x -= ~x & x + 1) {
    r = std::max(r, u[x]);
  }
  return r;
}

int sub(int* a, int n, int* path) {
  static int stack[N], f[N];
  int top = 0;
  stack[0] = -1;
  for (int i = 0; i < n; ++i) {
    if (a[i] > stack[top]) {
      stack[++top] = a[i];
      f[i] = top;
    } else {
      int l = 1, r = top;
      while (l <= r) {
        int m = (l + r) >> 1;
        if (a[i] > stack[m]) l = m + 1;
        else r = m - 1;
      }
      stack[l] = a[i];
      f[i] = l;
    }
  }
  int t = top;
  for (int i = n - 1; i >= 0; --i) {
    if (f[i] == t) {
      path[--t] = a[i];
    }
    if (t < 0) break;
  }
  return top;
}

int main() {
  srand(time(0));
  int T;
  scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      mark[a[i]] = 0;
    }
    std::vector<std::vector<int>> res;
    while (n) {
      std::vector<int> seq;
      int c1 = sub(a, n, s1);
      std::reverse(a, a + n);
      int c2 = sub(a, n, s2);
      std::reverse(s2, s2 + c2);
      std::reverse(a, a + n);
      if (c1 > c2) {
        for (int i = 0; i < c1; ++i) mark[s1[i]] = 1;
        seq = std::vector<int>(s1, s1 + c1);
      } else {
        for (int i = 0; i < c2; ++i) mark[s2[i]] = 1;
        seq = std::vector<int>(s2, s2 + c2);
      }
      int m = 0;
      for (int i = 0; i < n; ++i) {
        if (!mark[a[i]]) a[m++] = a[i];
      }
      n = m;
      res.push_back(seq);
    }
    printf("%d\n", (int)res.size());
    for (auto &&s: res) {
      printf("%d", (int)s.size());
      for (auto &&x: s) printf(" %d", x);
      puts("");
    }
  }
  return 0;
}