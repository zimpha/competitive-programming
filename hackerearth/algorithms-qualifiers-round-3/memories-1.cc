#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000;
int a[MAXN], b[MAXN], n, m;

void sol() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++ i) {
    scanf("%d%d", a + i, b + i);
    -- a[i]; -- b[i];
  }
  int s = 1 << n, ret(0);
  for (int msk = 1; msk < s; ++ msk) {
    bool flag = 1;
    for (int i = 0; i < m && flag; ++ i) {
      if ((msk >> a[i] & 1) && (msk >> b[i] & 1)) flag = 0;
    }
    ret += flag;
  }
  cout << ret << endl;
}

int main() {
  int T; scanf("%d", &T);
  while (T --) sol();
  return 0;
}
