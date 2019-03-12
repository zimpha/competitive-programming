#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

const int N = 300 + 10;

char s[N];
int f[N], g[N];
int pf[N], pg[N];

bool is_pal(int l, int r) {
  for (int i = l; i <= r; ++i) {
    if (s[i] != s[r - (i - l)]) return false;
  }
  return true;
}

int main() {
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; ++i) {
    f[i] = g[i] = -1;
  }
  f[0] = g[0] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) if ((i - j + 1) % 2 == 0 && is_pal(j, i)) {
      if (f[j - 1] != -1 && (f[i] == -1 || f[i] > f[j - 1] + 1)) {
        f[i] = f[j - 1] + 1;
        pf[i] = j - 1;
      }
      if (g[j - 1] != -1 && (g[i] == -1 || g[i] < g[j - 1] + 1)) {
        g[i] = g[j - 1] + 1;
        pg[i] = j - 1;
      }
    }
  }
  if (f[n] == -1) {
    puts("NIE");
    return 0;
  }
  std::vector<std::string> p;
  for (int i = n; i; i = pf[i]) {
    p.emplace_back(s + pf[i] + 1, s + i + 1);
  }
  std::reverse(p.begin(), p.end());
  for (int i = 0; i < f[n]; ++i) {
    if (i) putchar(' ');
    printf("%s", p[i].c_str());
  }
  puts("");
  p.clear();
  for (int i = n; i; i = pg[i]) {
    p.emplace_back(s + pg[i] + 1, s + i + 1);
  }
  std::reverse(p.begin(), p.end());
  for (int i = 0; i < g[n]; ++i) {
    if (i) putchar(' ');
    printf("%s", p[i].c_str());
  }
  puts("");
  return 0;
}
