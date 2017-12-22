#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m; cin >> n >> m;
  int ret = n;
  for (int i = 1; i <= n * 2; ++ i) {
    int tmp = abs(i - m);
    for (int j = i; j <= n * 2; j += i) {
      // i man, j banana
      ret = min(ret, tmp + abs(j - n));
    }
  }
  cout << ret << endl;
  return 0;
}
