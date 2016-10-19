#include <bits/stdc++.h>
using namespace std;

int sol() {
  vector<string> v;
  string s;
  while (cin >> s) {
    v.push_back(s);
  }
  sort(v.begin(), v.end());
  int ret(0);
  for (size_t i = 0; i < v.size(); ++ i) {
    int val(0);
    for (auto &c: v[i]) val += c - 'A' + 1;
    ret += (i + 1) * val;
  }
  return ret;
}

int main() {
  cout << sol() << endl;
  return 0;
}
