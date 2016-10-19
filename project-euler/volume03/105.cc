#include <bits/stdc++.h>
using namespace std;

int run() {
  string s; cin >> s;
  vector<int> a;
  int val = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] == ',') a.push_back(val), val = 0;
    else val = val * 10 + s[i] - '0';
  }
  a.push_back(val);
  vector<int> v, cnt(a.size() + 1, 0);
  int n = a.size();
  for (int o = 1; o <= n; ++o) {
    for (int msk = 0; msk < (1 << n); ++msk) {
      if (__builtin_popcount(msk) != o) continue;
      int s = 0; cnt[o]++;
      for (int i = 0; i < n; ++i) {
        if (msk >> i & 1) s += a[i];
      }
      v.push_back(s);
    }
  }
  for (int i = 1; i <= n; ++i) {
    cnt[i] += cnt[i - 1];
    sort(v.begin() + cnt[i - 1], v.begin() + cnt[i]);
  }
  for (size_t i = 1; i < v.size(); ++i) {
    if (v[i] <= v[i - 1]) return 0;
  }
  return v.back();
}

int main() {
  freopen("sets.txt", "r", stdin);
  int ret = 0;
  for (int i = 0; i < 100; ++i) {
    ret += run();
  }
  cout << ret << endl;
  return 0;
}
