#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

const int N = 1000;

std::vector<int> edges[N];
int vis[N], mate[N];

bool aug(int u) {
  for (auto &&v: edges[u]) if (!vis[v]) {
    vis[v] = 1;
    if (mate[v] == -1 || aug(mate[v])) {
      mate[v] = u;
      return true;
    }
  }
  return false;
}

bool intersect(const std::vector<int>& a, const std::vector<int> &b) {
  for (size_t i = 0, j = 0; i < a.size() && j < b.size(); ) {
    if (a[i] == b[j]) return true;
    else if (a[i] < b[j]) ++i;
    else ++j;
  }
  return false;
}

int main() {
  int n1, n2;
  scanf("%d%d", &n1, &n2);
  int n;
  scanf("%d", &n);
  std::vector<std::string> type(n);
  std::vector<std::vector<int>> hate(n), love(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> type[i];
    int x;
    while ((std::cin >> x) && x != -1) {
      love[i].push_back(x);
    }
    while ((std::cin >> x) && x != -1) {
      hate[i].push_back(x);
    }
    std::sort(love[i].begin(), love[i].end());
    std::sort(hate[i].begin(), hate[i].end());
  }
  for (int i = 0; i < n; ++i) if (type[i] == "A") {
    for (int j = 0; j < n; ++j) if (type[j] == "B") {
      if (intersect(love[i], hate[j]) || intersect(hate[i], love[j])) {
        edges[i].push_back(j);
      }
    }
  }
  int ret = n;
  for (int i = 0; i < n; ++i) mate[i] = -1;
  for (int i = 0; i < n; ++i) if (type[i] == "A") {
    for (int i = 0; i < n; ++i) vis[i] = 0;
    if (aug(i)) --ret;
  }
  printf("%d\n", ret);
  return 0;
}
