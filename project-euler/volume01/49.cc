#include <bits/stdc++.h>
using namespace std;

bool ok(int n) {
  if (n % 2 == 0) return 0;
  for (int i = 3; i * i <= n; ++ i) {
    if (n % i == 0) return 0;
  }
  return 1;
}

string toString(int n) {
  static char buf[100];
  sprintf(buf, "%d", n);
  sort(buf, buf + strlen(buf));
  return string(buf);
}

bool check(int x, int y, int z) {
  if (!ok(x) || !ok(y) || !ok(z)) return 0;
  string a = toString(x);
  string b = toString(y);
  string c = toString(z);
  return a == b && b == c && a == c;
}

void sol() {
  for (int a = 1000; a <= 9999; ++ a) {
    for (int b = 1; b <= 9999; ++ b) {
      if (a + b <= 9999 && a + b * 2 <= 9999) {
        if (check(a, a + b, a + b * 2)) {
          cout << a << a + b << a + b * 2 << endl;
        }
      }
    }
  }
}

int main() {
  sol();
  return 0;
}
