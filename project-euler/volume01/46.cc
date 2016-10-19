#include <bits/stdc++.h>
using namespace std;

int sol() {
  int n = 1000000;
  vector<int> vs(n, 1);
  vector<int> pl;
  vs[0] = vs[1] = 0;
  for (int i = 2; i < n; ++ i) if (vs[i]) {
    pl.push_back(i);
    for (int j = i + i; j < n; j += i) vs[j] = 0;
  }
  for (int i = 3; i < n; i += 2) if (!vs[i]) {
    bool flag(0);
    for (int j = 0; pl[j] < i && !flag; ++ j) {
      int x = i - pl[j], y = sqrt(x / 2);
      if (y * y * 2 == x) flag = 1;
    }
    if (!flag) return i;
  }
  return -1;
}

int main() {
  cout << sol() << endl;
  return 0;
}
