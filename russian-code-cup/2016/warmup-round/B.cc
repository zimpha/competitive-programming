#include <bits/stdc++.h>
using namespace std;

int main() {
  int n; scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  sort(a.begin(), a.end(), greater<int>());
  printf("%d\n", (a[0] + a[1]) / 2);
  return 0;
}
