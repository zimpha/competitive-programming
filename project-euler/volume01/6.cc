#include <bits/stdc++.h>
using namespace std;

int sol(int n) {
  int sum(0), res(0);
  for (int i = 1; i <= n; ++ i) {
    sum += i;
    res += i * i;
  }
  return sum * sum - res;
}

int main() {
  cout << sol(100) << endl;
  return 0;
}
