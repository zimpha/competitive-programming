#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  vector<int> vs(n, 1);
  vector<int> pl(1, 0);
  vs[0] = vs[1] = 0;
  for (int i = 2; i < n; ++ i) if (vs[i]) {
    pl.push_back(i + pl.back());
    for (int j = i + i; j < n; j += i) vs[j] = 0;
  }
  int ret(-1), mx(0);
  for (int i = 0; i < pl.size(); ++ i) {
    for (int j = i + 1; j < pl.size() && pl[j] - pl[i] < n; ++ j) {
      if (vs[pl[j] - pl[i]] && j - i > mx) {
        mx = j - i; ret = pl[j] - pl[i];
      }
    }
  }
  return ret;
}

int main() {
  cout << sol(100) << endl;
  cout << sol(1000) << endl;
  cout << sol(1000000) << endl;
  return 0;
}
