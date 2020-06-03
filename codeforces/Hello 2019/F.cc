#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <map>
#include <bitset>

using int64 = long long;

const int B = 7000 + 1, N = 1e5 + 10;

std::bitset<B> F[N];
std::vector<int> divisor[B];
std::bitset<B> M[B];
int mu[B];

int main() {
  for (int i = 1; i < B; ++i) {
    mu[i] ^= (i == 1);
    for (int j = i; j < B; j += i) {
      divisor[j].push_back(i);
      if (i < j) mu[j] ^= mu[i];
    }
  }
  for (int v = 1; v < B; ++v) {
    for (int d = 1; d < B; ++d) {
      if (d % v == 0) M[v][d] = mu[d / v];
    }
  }
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < q; ++i) {
    int op, x, y, z, v;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d", &x, &v);
      F[x] = 0;
      for (auto &&e: divisor[v]) F[x][e] = 1;
    } else if (op == 2) {
      scanf("%d%d%d", &x, &y, &z);
      F[x] = F[y] ^ F[z];
    } else if (op == 3) {
      scanf("%d%d%d", &x, &y, &z);
      F[x] = F[y] & F[z];
    } else {
      scanf("%d%d", &x, &v);
      auto tmp = M[v] & F[x];
      int ret = tmp.count() % 2;
      printf("%d", ret);
    }
  }
  puts("");
  return 0;
}