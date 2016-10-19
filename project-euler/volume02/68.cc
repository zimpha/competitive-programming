#include <bits/stdc++.h>
using namespace std;

string to(int n) {
  char buf[10];
  sprintf(buf, "%d", n);
  return string(buf);
}

int main() {
  int p[10];
  for (int i = 0; i < 10; ++ i) p[i] = i + 1;
  string ret = "";
  do {
    int s[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; ++ i) {
      s[i] = p[i] + p[(i + 1) % 5] + p[i + 5];
    }
    if (s[1] == s[0] && s[2] == s[0] && s[3] == s[0] && s[4] == s[0]) {
      string x;
      int ms = 5;
      for (int i = 5; i < 10; ++ i) {
        if (p[i] < p[ms]) ms = i;
      }
      for (int j = 0 ; j < 5; ++ j) {
        int i = (ms + j) % 5;
        x += to(p[i + 5]);
        x += to(p[i]) + to(p[(i + 1) % 5]);
      }
      if (x.size() == 16 && x > ret) ret = x;
    }
  } while (next_permutation(p, p + 10));
  cout << ret << endl;
  return 0;
}
