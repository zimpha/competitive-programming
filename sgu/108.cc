#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000, SIZE = 65535;
int s[MAXN], id[MAXN], n, m;
bool vis[SIZE + 1];

bool cmp(int a, int b) {
  return s[a] < s[b];
}

int get(int n) {
  int r(0);
  while (n) r += n % 10, n /= 10;
  return r;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++ i) scanf("%d", s + i), id[i] = i;
  sort(id, id + m, cmp);
  int ret(0);
  for (int i = 1, j = 0; i <= n; ++ i) {
    if (!vis[i & SIZE]) {
      ++ ret;
      while (j < m && s[id[j]] == ret) s[id[j ++]] = i;
    }
    int t = i + get(i);
    vis[t & SIZE] = 1;
    vis[i & SIZE] = 0;
  }
  printf("%d\n", ret);
  for (int i = 0; i < m; ++ i) printf("%d%c", s[i], " \n"[i == m - 1]);
  return 0;
}
