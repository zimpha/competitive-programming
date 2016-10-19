//http://www.geocities.ws/fredlb37/node9.html
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int MAXN = 120001;
vector<int> G[MAXN];
int deg[MAXN];

LL run(int n) {
  vector<PII> pq;
  for (int i = 1; i <= n; ++i) {
    G[i].clear(); deg[i] = 0;
  }
  for (int u = 1; u * u <= n; ++u) {
    for (int v = 1; v < u; ++v) if (__gcd(u, v) == 1) {
      if ((u - v) % 3 == 0) continue;
      int x = 2 * u * v + v * v;
      int y = u * u - v * v;
      if (x + y >= n) continue;
      for (int k = 1; (x + y) * k < n; ++k) {
        pq.push_back(PII(x * k, y * k));
        deg[k * x]++; deg[k * y]++;
      }
    }
  }
  for (auto &e: pq) {
    int x = e.first, y = e.second;
    if (deg[x] > deg[y]) G[x].push_back(y);
    else G[y].push_back(x);
  }
  static bool mark[MAXN];
  set<int> sol;
  LL ret = 0;
  for (auto &e: pq) {
    int x = e.first, y = e.second;
    for (auto v: G[x]) mark[v] = 1;
    for (auto v: G[y]) if (mark[v]) {
      if (x + y + v <= n) sol.insert(x + y + v);
    }
    for (auto v: G[x]) mark[v] = 0;
  }
  for (auto &x: sol) ret += x;
  return ret;
}

int main() {
  cout << run(120000) << endl;
  return 0;
}
