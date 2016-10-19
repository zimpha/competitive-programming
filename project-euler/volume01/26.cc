#include <bits/stdc++.h>
using namespace std;

int cycle(int n) {
  vector<int> v(n, 0);
  int a = 1;
  for (int i = 1; ; ++ i) {
    if (v[a]) return i - v[a];
    v[a] = i;
    a = a * 10 % n;
  }
  return -1;
}

int main() {
  int ret(0), mx(-1);;
  for (int d = 2; d < 1000; ++ d) {
    int c = cycle(d);
    if (c > mx) mx = c, ret = d;
  }
  cout << ret << endl;
  return 0;
}
