#include <bits/stdc++.h>
using namespace std;

template<int n>
int sol() {
  int sum(0);
  for (int i = 1; i < n; ++ i) {
    if (i % 3 == 0 || i % 5 == 0) {
      sum += i;
    }
  }
  return sum;
}

int main() {
  cout << sol<10>() << endl;
  cout << sol<1000>() << endl;
  return 0;
}
