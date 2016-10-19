#include <bits/stdc++.h>
using namespace std;

string toString(int n) {
  char buf[100];
  sprintf(buf, "%d", n);
  return string(buf);
}

int main() {
  string p = "123456789";
  string ret;
  do {
    int s(0);
    for (int l = 0; l < 4; ++ l) {
      s = s * 10 + p[l] - '0';
      string t = "";
      for (int i = 1; ; ++ i) {
        t += toString(i * s);
        if (t.size() >= 9) break;
      }
      if (p == t) ret = p;
    }
  } while (next_permutation(p.begin(), p.end()));
  cout << ret << endl;
  return 0;
}
