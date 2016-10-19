#include <bits/stdc++.h>
using namespace std;
const int N = 1000000;
int dsu[N], sz[N], rk[N];

int get(int x) {
  if (x != dsu[x]) dsu[x] = get(dsu[x]);
  return dsu[x];
}

int run(int pm) {
  for (int i = 0; i < N; ++i) dsu[i] = i, sz[i] = 1;
  int s[55], k = 0, mis = 0;
  while (sz[get(pm)] < N / 100 * 99) {
    int u, v;
    if (k < 55) u = s[k] = (100003 - 200003 * (k + 1) + 300007ll * (k + 1) * (k + 1) * (k + 1)) % N;
    else u = s[k % 55] = (s[(k - 24 + 55) % 55] + s[k % 55]) % N;
    ++k;
    if (k < 55) v = s[k] = (100003 - 200003 * (k + 1) + 300007ll * (k + 1) * (k + 1) * (k + 1)) % N;
    else v = s[k % 55] = (s[(k - 24 + 55) % 55] + s[k % 55]) % N;
    ++k;
    if (u == v) ++mis;
    u = get(u), v = get(v);
    if (v != u) dsu[u] = v, sz[v] += sz[u];
  }
  return k / 2 - mis;
}

int main() {
  cout << run(524287) << endl;
  return 0;
}
