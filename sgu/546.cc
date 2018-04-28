#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, a, b; scanf("%d%d%d", &n, &a, &b);
  if (a + b > n) puts("-1");
  else {
    string s; cin >> s;
    vector<int> p0, p1, p2;
    for (size_t i = 0; i < s.size(); ++i) {
      if (s[i] == '0') p0.push_back(i);
      if (s[i] == '1') p1.push_back(i);
      if (s[i] == '2') p2.push_back(i);
    }
    int ret = 0;
    while (p0.size() < a) {
      if (p1.size() > b) p0.push_back(p1.back()), p1.pop_back();
      else p0.push_back(p2.back()), p2.pop_back();
      ++ret;
    }
    while (p0.size() > a) {
      if (p1.size() < b) p1.push_back(p0.back()), p0.pop_back();
      else p2.push_back(p0.back()), p0.pop_back();
      ++ret;
    }
    while (p1.size() < b) {
      if (p0.size() > a) p1.push_back(p0.back()), p0.pop_back();
      else p1.push_back(p2.back()), p2.pop_back();
      ++ret;
    }
    while (p1.size() > b) {
      if (p0.size() < a) p0.push_back(p1.back()), p1.pop_back();
      else p2.push_back(p1.back()), p1.pop_back();
      ++ret;
    }
    for (auto &x: p0) s[x] = '0';
    for (auto &x: p1) s[x] = '1';
    for (auto &x: p2) s[x] = '2';
    printf("%d\n%s\n", ret, s.c_str());
  }
}
