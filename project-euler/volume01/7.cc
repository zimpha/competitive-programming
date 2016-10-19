#include <bits/stdc++.h>
using namespace std;

int sol(int m) {
  const int n = 1000000;
  static int pl[n];
  int s(0);
  for (int i = 2; i < n; ++ i) if (!pl[i]) {
    pl[s ++] = i;
    for (int j = i; j < n; j += i) pl[j] = 1;
  }
  return pl[m - 1];
}

int main() {
  cout << sol(10001) << endl;
  return 0;
}
