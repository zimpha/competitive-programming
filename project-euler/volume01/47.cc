#include <bits/stdc++.h>
using namespace std;

int sol() {
  int n = 1000000;
  vector<int> vs(n, 0);
  for (int i = 2; i < n; ++ i) if (!vs[i]) {
    for (int j = i; j < n; j += i) vs[j] ++;
  }
  for (int i = 1; i < n; ++ i) {
    if (vs[i] == 4 && vs[i + 1] == 4 && vs[i + 2] == 4 && vs[i + 3] == 4) {
      return i;
    }
  }
  return -1;
}

int main() {
  cout << sol() << endl;
  return 0;
}
