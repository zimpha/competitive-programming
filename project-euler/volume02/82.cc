#include <bits/stdc++.h>
using namespace std;

int sol(int n, int m) {
  vector<vector<int> > G;
  vector<int> val;
  vector<vector<int> > a;
  int N = n * m + 2;
  G.assign(N, vector<int>());
  a.assign(n, vector<int>());
  val.assign(N, 0);
  for (int i = 0; i < n; ++ i) {
    for (int j = 0; j < m; ++ j) {
      int x; cin >> x;
      a[i].push_back(x);
      val[i * m + j] = x;
    }
  }
  const int dx[] = {1, 0, -1};
  const int dy[] = {0, 1, 0};
  for (int i = 0; i < n; ++ i) {
    G[N - 2].push_back(i * m);
    G[i * m + m - 1].push_back(N - 1);
    for (int j = 0; j < m; ++ j) {
      int u = i * m + j;
      for (int k = 0; k < 3; ++ k) {
        int x = i + dx[k], y = j + dy[k];
        if (x < 0 || x >= n || y < 0 || y >= m) continue;
        G[u].push_back(x * m + y);
      }
    }
  }
  vector<int> dis(N, 1e9);
  vector<bool> vs(N, 0);
  int S = N - 2, T = N - 1;
  dis[S] = 0; vs[S] = 1;
  queue<int> Q; Q.push(S);
  while (!Q.empty()) {
    int u = Q.front(); Q.pop(); vs[u] = 0;
    for (auto &v: G[u]) {
      if (dis[v] > dis[u] + val[v]) {
        dis[v] = dis[u] + val[v];
        if (!vs[v]) vs[v] = 1, Q.push(v);
      }
    }
  }
  return dis[T];
}

int main() {
  cout << sol(80, 80) << endl;
  return 0;
}
