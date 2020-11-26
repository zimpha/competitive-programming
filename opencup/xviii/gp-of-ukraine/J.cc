#include <cstdio>
#include <cstring>

using i64 = long long;

const int N = 1e7 + 64;

unsigned s; // s in the value given in the input
unsigned getNext() {
  s = s xor (s << 13);
  s = s xor (s >> 17);
  s = s xor (s << 5);
  return s;
}

int best[N];
i64 weight[N];
unsigned ret[N / 32];

int main() {
  int n, m;
  scanf("%d%d%u", &n, &m, &s);
  memset(best, -1, sizeof(int) * n);
  for (int i = 0; i < m; ++i) {
    int u = getNext() % n;
    int v = getNext() % n;
    i64 w = getNext() / 4;
    w = w * getNext(); // watch out for integer overflow
    if (u == v) continue;
    if (best[u] == -1 || weight[u] > w) {
      best[u] = i;
      weight[u] = w;
    }
    if (best[v] == -1 || weight[v] > w) {
      best[v] = i;
      weight[v] = w;
    }
  }
  for (int i = 0; i < n; ++i) {
    int e = best[i];
    ret[e / 32] |= i64(1) << (e % 32);
  }
  for (int i = 0; i < (m + 31) / 32; ++i) {
    printf("%u ", ret[i]);
  }
  puts("");
  return 0;
}
