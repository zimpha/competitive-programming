#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500000 + 10;
bool f[MAXN][20];

int main() {
  int n, k, m; cin >> n >> k >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++ i) cin >> b[i];
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  if (m && b[0] == 0) b.erase(b.begin());
  m = b.size();
  set<int> s(b.begin(), b.end());
  if (m == 0 || b[0] != 1) {
    putchar('1');
    int cnt = 1; k = min(k, 19);
    for (int i = 1; i < 20; ++ i) f[1][i] = 1;
    for (int i = 2; cnt < n; ++ i) if (!s.count(i) && !f[i][k]) {
      ++ cnt;
      printf(" %d", i);
      f[i][1] = 1;
      for (int j = 2; j < 20; ++ j) {
        for (int x = i; x < MAXN; x += i) {
          f[x][j] |= f[x / i][j - 1];
        }
      }
    }
    puts("");
    cerr << cnt << endl;
  } else {
    int tar = 2;
    while (s.count(tar)) ++ tar;
    for (int i = 0; i < n; ++ i) printf("%d ", tar);
    puts("");
  }
  return 0;
}
