#include <bits/stdc++.h>

int main() {
  int n, a, b;
  std::scanf("%d%d%d", &n, &a, &b);
  std::vector<int> t(n);
  for (int i = 0; i < n; ++i) scanf("%d", &t[i]);
  std::vector<int> unread;
  for (int i = 0, j = 0; i <= 100000; ++i) {
    if (j < n && t[j] == i) unread.push_back(i), ++j;
    if (unread.size() == a || (unread.size() && unread[0] + b == i)) {
      int s = unread.size() / 2 + unread.size() % 2;
      for (int k = 0; k < s; ++k) {
        printf("%d ", i);
      }
      unread.erase(unread.begin(), unread.begin() + s);
    }
  }
  puts("");
  return 0;
}
