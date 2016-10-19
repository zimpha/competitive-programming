#include <bits/stdc++.h>
using namespace std;

int sol() {
  string s;
  int ret(0);
  while (cin >> s) {
    int v(0);
    for (auto &c: s) v += c - 'A' + 1;
    int n = sqrt(v * 2);
    if (n * (n + 1) == v * 2) ++ ret;
  }
  return ret;
}

int main() {
  cout << sol() << endl;
  return 0;
}
