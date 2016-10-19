#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  vector<int> cnt(n + 1, 0);
  for (int a = 1; a < n; ++ a) {
    for (int b = a + 1; b < n; ++ b) {
      int c = sqrt(a * a + b * b);
      if (c * c == a * a + b * b && a + b + c <= n) {
        cnt[a + b + c] ++;
      }
    }
  }
  return max_element(cnt.begin(), cnt.end()) - cnt.begin();
}

int main() {
  cout << sol(1000) << endl;
  return 0;
}
