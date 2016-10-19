#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("words.txt", "r", stdin);
  vector<string> words;
  vector<string> square;
  for (int i = 1; i * i < 1e9; ++i) {
    char buf[1000]; sprintf(buf, "%d", i * i);
    square.push_back(buf);
  }
  string s;
  while (cin >> s) words.push_back(s);
  int mx = 0;
  for (size_t i = 0; i < words.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      string s = words[i], t = words[j];
      sort(s.begin(), s.end());
      sort(t.begin(), t.end());
      if (s != t) continue;
      for (auto s: square) if (s.length() == t.length()) {
        map<char, int> mp;
        set<int> used;
        bool flag = true;
        for (size_t x = 0; x < s.length() && flag; ++x) {
          int d = s[x] - '0';
          char c = words[i][x];
          if (mp.count(c)) {
            if (mp[c] == d) continue;
            else flag = false;
          }
          if (used.count(d)) flag = false;
          mp[c] = d; used.insert(d);
        }
        if (!flag) continue;
        if (mp[words[j][0]] == 0) continue;
        int wi = 0, wj = 0;
        for (size_t x = 0; x < s.length(); ++x) {
          wi = wi * 10 + mp[words[i][x]];
          wj = wj * 10 + mp[words[j][x]];
        }
        int tmp = sqrt(wj + 1);
        if (tmp * tmp == wj) {
          cerr << wi << " " << wj << endl;
          mx = max(mx, max(wi, wj));
        }
      }
    }
  }
  cerr << mx << endl;
  return 0;
}
