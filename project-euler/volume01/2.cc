#include <bits/stdc++.h>
using namespace std;

template<int n>
int sol() {
  int sum(0), a(1), b(1);
  for (; ;) {
    int c = a + b;
    if (c > n) break;
    if (c % 2 == 0) sum += c;
    a = b; b = c;
  }
  return sum;
}

int main() {
  cout << sol<4000000>() << endl;
  return 0;
}
