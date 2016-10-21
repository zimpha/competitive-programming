#include <bits/stdc++.h>

const int N = 100000 + 10, M = 128;

int sg[N];

void prepare() {
  for (int n = 0; n < N; ++n) {
    std::set<int> s;
    for (int i = 1; i * i <= n; ++i) {
      s.insert(sg[n - i * i]);
    }
    while (s.count(sg[n])) ++sg[n];
  }
}

long run(int n) {
  long ca[M], cb[M], ret = 0;
  memset(ca, 0, sizeof(ca));
  memset(cb, 0, sizeof(cb));
  for (int i = 0; i <= n; ++i) {
    ca[sg[i]]++;
    for (int x = 0; x < M; ++x) {
      cb[sg[i] ^ x] += ca[x];
    }
    ret += cb[sg[i]];
  }
  return ret;
}

int main() {
  prepare();
  std::cout << run(29) << std::endl;
  std::cout << run(100000) << std::endl;
  return 0;
}
