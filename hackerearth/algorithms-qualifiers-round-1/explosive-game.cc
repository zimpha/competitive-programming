#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 100000 + 10;

map<int, vector<PII> > mp;
int a[MAXN], b[MAXN];
int n, q;

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++ i) {
    scanf("%d%d", a + i, b + i);
    if (a[i] > b[i]) swap(a[i], b[i]);
    mp[b[i] - a[i]].push_back(PII(a[i], b[i]));
  }
  bool flag = true;
  LL S1min(0), S1max(0);
  LL S2min(0), S2max(0);
  for (auto &x: mp) {
    vector<PII> &v = x.second;
    flag &= v.size() % 2 == 0;
    if (!flag) break;
    sort(v.begin(), v.end());
    for (size_t i = 0; i < v.size(); ++ i) {
      if (i & 1) S1min += v[i].first, S1max += v[i].second;
      else S2min += v[i].first, S2max += v[i].second;
    }
    /*
    if (v[0] == v.back()) {
      S1min += 1ll * v[0].first * v.size() / 2;
      S2min += 1ll * v[0].first * v.size() / 2;
      S1max += 1ll * v[0].second * v.size() / 2;
      S2max += 1ll * v[0].second * v.size() / 2;
    }
    else flag = 0;
    */
  }
  LL tot = S1min + S2max;
  for (int i = 0; i < q; ++ i) {
    LL x; scanf("%lld", &x);
    if (flag) puts(x == tot ? "YES" : "NO");
    else puts("NO");
  }
  return 0;
}
