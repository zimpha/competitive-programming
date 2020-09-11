#include <cstdio>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using pis = std::pair<int, std::string>;

bool query(const std::string &s) {
  printf("? %s\n", s.c_str());
  fflush(stdout);
  static char buf[100];
  scanf("%s", buf);
  return buf[0] == 'Y';
}

int main() {
  std::priority_queue<pis, std::vector<pis>, std::greater<pis>> pq;
  for (char c = 'a'; c <= 'z'; ++c) {
    int k = 0;
    while (query(std::string(1 << k, c))) k++;
    if (k == 0) continue;
    int l = 1 << (k - 1);
    for (k -= 2; k >= 0; --k) {
      if (query(std::string(l + (1 << k), c))) l += 1 << k;
    }
    pq.emplace(l, std::string(l, c));
  }
  while (pq.size() != 1) {
    auto x = pq.top().second; pq.pop();
    auto y = pq.top().second; pq.pop();
    std::string s;
    size_t i = 0, j = 0;
    while (i < x.size() && j < y.size()) {
      if (query(s + x[i] + y.substr(j))) s += x[i++];
      else s += y[j++];
    }
    s += x.substr(i);
    s += y.substr(j);
    pq.emplace(s.size(), s);
  }
  printf("! %s\n", pq.top().second.c_str());
  fflush(stdout);
  return 0;
}
