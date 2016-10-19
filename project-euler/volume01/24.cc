#include <bits/stdc++.h>
using namespace std;

void sol(int n) {
  int p[10];
  for (int i = 0; i < 10; ++ i) p[i] = i;
  for (int _ = 1; _ < n; ++ _) {
    next_permutation(p, p + 10);
  }
  for (int i = 0; i < 10; ++ i) cout << p[i]; 
  cout << endl;
}

int main() {
  sol(1000000);
  return 0;
}
