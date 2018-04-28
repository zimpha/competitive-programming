#include <bits/stdc++.h>
using namespace std;

void run() {
  int n, t1, t2; cin >> n >> t1 >> t2;
  int l = 0, r = n * max(t1, t2);
  while (l < r) {
    int m = (l + r - 1) >> 1;
    if (m / t1 + m / t2 >= n) r = m;
    else l = m + 1;
  }
  int m = l / t1 + (l % t1 != 0) + l / t2 + (l % t2 != 0);
  int f = max(t1 * (l / t1 + (l % t1 != 0)), t2 * (l / t2 + (l % t2 != 0)));
  cout << m << " " << f << endl;
}

int main() {
  run();
  return 0;
}
