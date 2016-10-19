#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1000000 + 10;

int pl[MAXN], m;

int run(LL lim) {
  for (int i = 1; i <= m; i += 2) {
    if (2ll * i * pl[i] % (1ll * pl[i] * pl[i]) > lim) {
      return i;
    }
  }
  return -1;
}

int main() {
  for (int i = 2; i < MAXN; ++i) if (!pl[i]) {
    pl[++m] = i;
    for (int j = i + i; j < MAXN; j += i) pl[j] = 1;
  }
  cout << run(1e9) << endl;
  cout << run(1e10) << endl;
  return 0;
}
