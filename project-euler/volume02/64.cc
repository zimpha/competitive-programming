//http://oeis.org/A013943/b013943.txt
#include <bits/stdc++.h>
using namespace std;

int main() {
  int ret(0);
  for (int i = 1; i <= 10000; ++ i) {
    int x = sqrt(i);
    if (x * x == i) continue;
    int a, b; cin >> a >> b;
    ret += b & 1;
  }
  cout << ret << endl;
  return 0;
}
