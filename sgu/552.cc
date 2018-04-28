#include <bits/stdc++.h>
using namespace std;
typedef vector<int> VI;

map<VI, int> mp;
map<string, int> idx;
int getIdx(string s) {
  if (idx.count(s)) return idx[s];
  int r = idx.size();
  return idx[s] = r;
}

void run() {
  int n; scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int l; scanf("%d", &l);
    VI pt;
    while (l--) {
      char s[100]; scanf("%s", s);
      pt.push_back(getIdx(s));
    }
    sort(pt.begin(), pt.end());
    for (int msk = 1; msk < (1 << pt.size()); ++msk) {
      VI key;
      for (int i = 0; i < pt.size(); ++i) {
        if (msk >> i & 1) key.push_back(pt[i]);
      }
      mp[key]++;
    }
  }
  int m; scanf("%d", &m);
  for (int _ = 0; _ < m; ++_) {
    int l; scanf("%d", &l);
    VI key;
    while (l--) {
      char s[100]; scanf("%s", s);
      key.push_back(getIdx(s));
    }
    sort(key.begin(), key.end());
    if (mp.count(key)) printf("%d\n", mp[key]);
    else puts("0");
  }
}

int main() { 
  run();
  return 0;
}
