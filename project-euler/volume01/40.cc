#include <bits/stdc++.h>
using namespace std;

int d(int n) {
  int s(0);
  for (int i = 1; ; ++ i) {
    static char buf[10];
    sprintf(buf, "%d", i);
    s += strlen(buf);
    if (s >= n) {
      return buf[n - s + strlen(buf) - 1] - '0';
    }
  }
  return 0;
}

int main() {
  cout << d(1) * d(10) * d(100) * d(1000) * d(10000) * d(100000) * d(1000000) << endl;
  return 0;
}
