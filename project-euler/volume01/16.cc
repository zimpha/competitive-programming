#include <bits/stdc++.h>
using namespace std;

int sol() {
  string s; cin >> s;
  int ret(0);
  for (auto &c: s) ret += c - '0';
  return ret;
}

int main() {
  cout << sol() << endl;
  return 0;
}
