#include <bits/stdc++.h>

using LL = long long;
const int M = 500500507;

LL run(int n) {
  int upp = n * 20;
  std::vector<int> p;
  std::vector<bool> mark(upp);
  for (int i = 2; i < upp; ++i) if (!mark[i]) {
    p.push_back(i);
    for (int j = i; j < upp; j += i) mark[j] = 1;
  }
  std::priority_queue<LL, std::vector<LL>, std::greater<LL>> pq;
  LL ret = 1;
  for (int i = 0; i < n; ++i) pq.push(p[i]);
  for (int i = 0; i < n; ++i) {
    LL val = pq.top();
    pq.pop();
    pq.push(val * val);
    ret = ret * val % M;
  }
  return ret;
}

int main() {
  std::cout << run(4) << std::endl;
  std::cout << run(500500) << std::endl;
  return 0;
}

